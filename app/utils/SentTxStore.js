import os from 'os';
import path from 'path';
import fs from 'fs';
import { remote } from 'electron';
import { Transaction, TxDetail } from '../components/AppState';
import parseMemo from './parseMemo';

export default class SentTxStore {
  static async writeSentTx(sentTx) {
    const fileName = await this.locateSentTxStore();

    if (!fs.existsSync(fileName)) {
      await fs.promises.writeFile(fileName, JSON.stringify([sentTx]));
      return;
    }

    fs.readFile(fileName, async (err, data) => {
      const json = JSON.parse(data);

      json.push(sentTx);

      await fs.promises.writeFile(fileName, JSON.stringify(json));
    });
  }

  static locateSentTxStore() {
    if (os.platform() === 'darwin') {
      return path.join(remote.app.getPath('appData'), 'Arrow', 'senttxstore.dat');
    }

    if (os.platform() === 'linux') {
      return path.join(
        remote.app.getPath('home'),
        '.local',
        'share',
        'zec-qt-wallet-org',
        'zec-qt-wallet',
        'senttxstore.dat'
      );
    }

    return path.join(remote.app.getPath('appData'), 'Arrow', 'senttxstore.dat');
  }

  static async loadSentTxns(): Transaction[] {
    try {
      const transactions = JSON.parse(await fs.promises.readFile(this.locateSentTxStore()));

      return transactions.map(transaction => {
        const txRes = transaction.result[0];
        const { params } = txRes;
        const { amounts } = params;

        const transction = new Transaction();
        transction.type = 'send';
        transction.amount = amounts[0].amount;
        transction.address = params.fromaddress;
        transction.txid = txRes.result.txid;
        transction.time = txRes.creation_time;
        transction.detailedTxns = [new TxDetail()];
        transction.detailedTxns[0].address = amounts[0].address;
        transction.detailedTxns[0].amount = amounts[0].amount;
        transction.detailedTxns[0].memo = amounts[0].memo ? parseMemo(amounts[0].memo) : '';

        return transction;
      });
    } catch (err) {
      // If error for whatever reason (most likely, file not found), just return an empty array
      console.error(err);
      return [];
    }
  }
}
