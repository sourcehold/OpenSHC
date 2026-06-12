# OpenSHC [![sourcehold](https://discordapp.com/api/guilds/1259903348077756527/widget.png?style=shield)](https://discord.gg/SKJGEGgPTv)
[Join our Discord Server!](http://discord.gg/SKJGEGgPTv)

An open source re-implementation of Stronghold Crusader 1. The beloved Castle Building, Real Time Strategy, and Simulation game reimplemented.

For running and developing this re-implementation, you need to own Stronghold Crusader 1.41 (Latin version), preferably from Steam or GOG.

## Motivation

The original game is a masterpiece, seeing new reignited popularity since the release of the Definitive Edition.
However, the Definitive Edition does not address various shortcomings in the original game.
Furthermore, the new Definitive Edition requires modern hardware to run, which isn't something all fans can afford.

This reimplementation seeks to cater to the wishes of the dedicated community by providing an
open source reimplementation that benefits modding to those that own the original Stronghold Crusader (available from Steam and GOG).

## Usage

OpenSHC builds as a DLL that is loaded at game start. Functions that have a functionally identical reimplementation are hooked, such that the reimplemented versions are run instead of the original. This enables easy modding, although modding itself is currently beyond the scope of the OpenSHC project. Instead, the project currently focuses on reimplementing functionality.

## Contribute

The development of this reimplementation is a stepwise process in which we aim to achieve a functionally identical reimplementation. We track progress using various tools.

All developers are welcome to contribute.

Get an overview [here](https://sourcehold.github.io/OpenSHC/wiki.html) or dive straight in [here](https://sourcehold.github.io/OpenSHC/wiki/tutorials/reimplementation-tutorial-0.html)!

### Requirements

Before you begin, install the following:

* **Stronghold Crusader 1.41 (Latin version)**
  
  The Steam release is the easiest version to obtain. Make sure the game installation uses a Latin-language version such as English or German.

* **CMake 3.24 or later**
  
  You can install it from:

  * [https://cmake.org/download/](https://cmake.org/download/)
  * [https://github.com/Kitware/CMake/releases/](https://github.com/Kitware/CMake/releases/)

  If you already installed the Microsoft Visual C++ Development Tools, you can also install CMake through Visual Studio.

* **Python 3**

* **clang-format 22 or later**
  
  Install it with:

  ```bash
  python -m pip install clang-format
  ```

* **An IDE with CMake support (recommended)**
  
  The repository is optimized for Visual Studio Code with the Microsoft C/C++ Extension Pack.
  
  To automatically format and style new C++ files, install the clang-format Extension Pack.

---

### Setup

#### 1. Clone the repository

Clone the repository with submodules included:

```bash
git clone --recursive https://github.com/sourcehold/OpenSHC.git
```

Then enter the project directory:

```bash
cd OpenSHC
```

> The `--recursive` flag is required because the repository depends on submodules, including the compiler.

---

#### 2. Create a symbolic link to the original game

Run the following batch file:

```bash
softlink.bat
```

The script will ask for the full path to your Stronghold Crusader installation directory.

After the link is created, a folder named `_original` will appear in the repository root.

> This script may require administrator privileges to be able to create the symbolic link

---

#### 3. Set up the Python environment for binary comparison

To set up the binary comparison tools, run:

```bash
reccmp\dll\setup.bat
```

> In the future, if you want to setup comparison of the reimplemented executable instead of the DLL, use:
> ```bash
> reccmp\exe\setup.bat
> ```

---

### Verifying the Setup

If **both** commands complete successfully, your development environment is ready and you can start working on OpenSHC.

#### 1. Build the project

From the `OpenSHC` directory, run:

```bash
build.bat RelWithDebInfo OpenSHC.dll
```

---

#### 2. Run binary comparison

This verifies byte-level accuracy between the reimplementation and the original binary:

```bash
reccmp/dll/run reccmp-reccmp --target STRONGHOLDCRUSADER
```

> Tip: use `reccmp/dll/run reccmp-reccmp --target STRONGHOLDCRUSADER --verbose <hex address of function>` to investigate code byte mismatches.

---

## Tutorials

When you are set up, follow any of the tutorials such as [this one](https://sourcehold.github.io/OpenSHC/wiki/tutorials/reimplementation-tutorial-1.html) to get you started!

## Help

Raise an issue here on GitHub to receive support. Or visit the [Discord](https://discord.gg/SKJGEGgPTv) server.
