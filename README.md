# OpenSHC
An open source re-implementation of Stronghold Crusader 1. The beloved Castle Building, Real Time Strategy, and Simulation game remastered.

## Download and Install
This reimplementation requires you to own a legal copy of the original Stronghold Crusader game from Firefly Studios.

The current method of installation is via the [Unofficial Crusader Patch](https://github.com/UnofficialCrusaderPatch/UnofficialCrusaderPatch). Make sure to set that up first.

0. Set up the Unofficial Crusader Patch.
1. Download the latest release of the reimplementation from the Releases page of this repo.
2. Launch the GUI from the Unofficial Crusader Patch.
3. Drag and drop the zip file unto your open UCP3 GUI, or manually move the zip file into the `ucp/modules` folder inside your game folder.
4. Reload the UCP3 GUI and activate the module.
5. Disable Security in the Launch tab of the GUI.
5. Launch the game!

## Help
Raise an issue here on GitHub to receive support. Or visit the [Discord](https://discord.gg/27W68ZaFT4) server.

## About
The project aims to provide a faithful open source reimplementation of the game that works on Windows 10+, Linux, and MacOS.

## Contribute
The development of this reimplementation is a stepwise process. All developers are welcome to contribute.

### Development
The development of this reimplementation primarily focuses on reimplementing functions and data structures of the original game.

We use [reccmp](https://github.com/isledecomp/reccmp) to verify compatibility of reimplemented code and the original game.

The game 1.41 Latin version of the Stronghold Crusader executable serves as the reference point (SHA hash: 012E9D55DAC04B23ED9A334C975D3A5B6287020B).

Collaboration on this version of the game happens via tools such as GitHub, Ghidra, x64dbg, and other tools.

Join the [Discord](https://discord.gg/27W68ZaFT4) server to learn more!

### Approach
The approach of this reimplementation is to provide a Windows DLL file that reimplements functionality of the original game.

Thus, we reimplement the game function by function. The Windows DLL is included into the original Stronghold Crusader process.

Faithfulness to the original game is verified using `reccmp`. Because the original game was compiled using an old compiler, you have to compile it using [this compiler](https://github.com/sourcehold/MSVC1400).