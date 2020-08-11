Quiver Fullnode is a wallet and full node for arrowd that runs on Linux, Windows and macOS.

![Screenshot](resources/screenshot1.png?raw=true)
![Screenshots](resources/screenshot2.png?raw=true)

# Installation

**Note**: Quiver Fullnode will download the entire blockchain (about 26GB), and requires some familiarity with the command line. If you don't want to download the blockchain but prefer a Lite wallet, please check out [Quiver Lite](https://github.com/Arrowchain/quiver-lite/releases/tag/v1.0.2).

Head over to the releases page and grab the latest installers or binary. https://github.com/Arrowchain/quiver/releases

### Linux

If you are on Debian/Ubuntu, please download the '.AppImage' package and just run it.

```
./Quiver.Fullnode-0.9.11.AppImage
```

If you prefer to install a `.deb` package, that is also available.

```
sudo dpkg -i quiver_0.9.11_amd64.deb
sudo apt install -f
```

### Windows

Download and run the `.msi` installer and follow the prompts. Alternately, you can download the release binary, unzip it and double click on `quiver.exe` to start.

### macOS

Double-click on the `.dmg` file to open it, and drag `Quiver Fullnode` on to the Applications link to install.

## arrowd

Quiver needs an Arrow node running arrowd. If you already have a arrowd node running, Quiver will connect to it.

If you don't have one, Quiver will start its embedded arrowd node.

Additionally, if this is the first time you're running Quiver or a arrowd daemon, Quiver will download the Arrow params (~777 MB) and configure `arrow.conf` for you.

## Compiling from source

Quiver is written in Electron/Javascript and can be build from source. Note that if you are compiling from source, you won't get the embedded arrowd by default. You can either run an external arrowd, or compile arrowd as well.

#### Pre-Requisits

You need to have the following software installed before you can build Quiver Fullnode

- Nodejs v12.16.1 or higher - https://nodejs.org
- Yarn - https://yarnpkg.com

```
git clone https://github.com/Arrowchain/quiver.git
cd quiver

yarn install
yarn build
```

To start in development mode, run

```
yarn dev
```

To start in production mode, run

```
yarn start
```

### [Troubleshooting Guide & FAQ](https://github.com/Arrowchain/quiver/wiki/Troubleshooting-&-FAQ)

Please read the [troubleshooting guide](https://docs.zecwallet.co/troubleshooting/) for common problems and solutions.
For support or other questions, tweet at [@zecwallet](https://twitter.com/zecwallet) or [file an issue](https://github.com/Arrowchain/quiver/issues).
