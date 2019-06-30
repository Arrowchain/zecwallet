#include "debugdialog.h"
#include "ui_debugdialog.h"
#include "settings.h"
#include "mainwindow.h"
#include "rpc.h"
#include "settings.h"

#include "precompiled.h"
#include<QDebug>

DebugDialog::DebugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebugDialog)
{
    ui->setupUi(this);
}

DebugDialog::~DebugDialog()
{
    delete ui;
}

void DebugDialog::setupDialog(MainWindow* main, QDialog* d, Ui_DebugDialog* dbg) {
    dbg->setupUi(d);
//    Settings::saveRestore(d);

//    // Setup
//    req->txtMemo->setLenDisplayLabel(req->lblMemoLen);
//    req->lblAmount->setText(req->lblAmount->text() + Settings::getTokenName());

    if (!main || !main->getRPC())
        return;

//    for (auto addr : *main->getRPC()->getAllZAddresses()) {
//        auto bal = main->getRPC()->getAllBalances()->value(addr);
//        if (Settings::getInstance()->isSaplingAddress(addr)) {
//            req->cmbMyAddress->addItem(addr, bal);
//        }
//    }
//    req->cmbMyAddress->setCurrentText(main->getRPC()->getDefaultSaplingAddress());

//    QIcon icon(":/icons/res/paymentreq.gif");
//    req->lblPixmap->setPixmap(icon.pixmap(48, 48));
}

// Static method that shows the request dialog
void DebugDialog::showDebug(MainWindow* main) {
    QDialog d(main);
    Ui_DebugDialog dbg;

    setupDialog(main, &d, &dbg);

    // wire up cli submit
    QObject::connect(dbg.btnSendDebug, &QPushButton::clicked, [=] () {
        QString command = dbg.txtDebugInput->toPlainText();
        qDebug() << command;

        std::string input = command.toUtf8().constData();
        std::string method = input.substr(0, input.find(" "));
        qDebug() << QString::fromStdString(method);
        json payload = {};
        bool parseError = false;
        if (input.find(" ") > input.length()) {
            payload = {
                {"jsonrpc", "1.0"},
                {"id", "someid"},
                {"method", method}
            };
        } else {
            std::string everythingElse = input.substr(input.find(" ") + 1);
            qDebug() << QString::fromStdString(everythingElse);
            json params;
            try {
                params = json::parse(everythingElse);
            } catch(int err) {
                parseError = true;
            }

            if (!parseError) {
                payload = {
                    {"jsonrpc", "1.0"},
                    {"id", "someid"},
                    {"method", method},
                    {"params", params}
                };
            }
        }


        std::string strJson = payload.dump();
        qDebug() << QString::fromStdString(strJson);
        if (!parseError) {
            dbg.txtDebugOutput->setPlainText(QString::fromStdString(strJson));
            main->getRPC()->sendAnything(payload, [=](const json& reply) {
                std::string response = reply.dump();
                dbg.txtDebugOutput->setPlainText(QString::fromStdString(response));
            },
            [=](QString errStr) {
               dbg.txtDebugOutput->setPlainText(errStr);
            });
        }

    });

//    // Setup the Label completer for the Address
//    req.txtFrom->setCompleter(main->getLabelCompleter());
//    QObject::connect(req.txtFrom, &QLineEdit::textChanged, [=] (auto text) {
//        auto addr = AddressBook::addressFromAddressLabel(text);
//        if (!Settings::getInstance()->isSaplingAddress(addr)) {
//            req.lblSaplingWarning->setText(tr("Can only request from Sapling addresses"));
//            req.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
//        } else {
//            req.lblSaplingWarning->setText("");
//            req.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
//        }
//    });

//    // Wire up AddressBook button
//    QObject::connect(req.btnAddressBook, &QPushButton::clicked, [=] () {
//        AddressBook::open(main, req.txtFrom);
//    });

//    // Amount textbox
//    req.txtAmount->setValidator(main->getAmountValidator());
//    QObject::connect(req.txtAmount, &QLineEdit::textChanged, [=] (auto text) {
//        req.txtAmountUSD->setText(Settings::getUSDFromZecAmount(text.toDouble()));
//    });
//    req.txtAmountUSD->setText(Settings::getUSDFromZecAmount(req.txtAmount->text().toDouble()));

//    req.txtMemo->setAcceptButton(req.buttonBox->button(QDialogButtonBox::Ok));
//    req.txtMemo->setLenDisplayLabel(req.lblMemoLen);
//    req.txtMemo->setMaxLen(400);

//    req.txtFrom->setFocus();

    if (d.exec() == QDialog::Accepted) {
//        // Construct a zcash Payment URI with the data and pay it immediately.
//        QString memoURI = "zcash:" + req.cmbMyAddress->currentText()
//                    + "?amt=" + Settings::getDecimalString(req.txtAmount->text().toDouble())
//                    + "&memo=" + QUrl::toPercentEncoding(req.txtMemo->toPlainText());

//        QString sendURI = "zcash:" + AddressBook::addressFromAddressLabel(req.txtFrom->text())
//                    + "?amt=0.0001"
//                    + "&memo=" + QUrl::toPercentEncoding(memoURI);

//        // If the disclosed address in the memo doesn't have a balance, it will automatically fallback to the default
//        // sapling address
//        main->payZcashURI(sendURI, req.cmbMyAddress->currentText());
    }


}
