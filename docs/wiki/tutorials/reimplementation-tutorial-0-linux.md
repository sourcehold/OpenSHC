## Tutorial 0: Getting Started (Linux using Wine)

### Requirements

Before you begin, install the following:

* **wine**

  For example, on ARCH Linux use: `pacman -S wine`.
  
* **CMake 3.24 or later**

  Also make sure to install cmake from [here](https://github.com/Kitware/CMake/releases/download/v4.4.0/cmake-4.4.0-windows-x86_64.msi) or [here](https://cmake.org/download/) and install it using wine, i.e., run `wine cmd` from a bash prompt and from within that prompt run the cmake .msi file. Exit and launch a new `wine cmd` to have cmake in your PATH.

* **Stronghold Crusader 1.41 (Latin version)**
  
  The Steam release is the easiest version to obtain. Make sure the game installation uses a Latin-language version such as English or German. Copy all binaries such as .dll and .exe to a directory named `_original` in the repository root.

* **Python 3**

  You need this in Linux, it is not recommended in wine (Windows environment).

* **clang-format 22 or later**
   
  In (arch) linux use:

  ```bash
  pipx install clang-format
  ``` 

  Other linux distributions may have its own method for installing using pip.

  Ensure `clang-format` is in the `$PATH` by running `pipx ensurepath`. Exit and launch a new bash shell to have clang-format in your PATH.

* **An IDE with CMake support (recommended)**

  > This section was written for Windows not Linux. It might not apply for Linux.
  
  The repository is optimized for Visual Studio Code with the Microsoft C/C++ Extension Pack.
  
  To automatically format and style new C++ files, install the clang-format Extension Pack.

---

## Setup

### 1. Clone the repository

Clone the repository with submodules included:

```bash
git clone --recursive https://github.com/sourcehold/OpenSHC.git
```

Then enter the project directory:

```bash
cd OpenSHC
```

> The `--recursive` flag is required because the repository depends on submodules, including the compiler.


#### Applying Linux specific patches

Apply the custom `mt.exe` and other patches:

```bash
cp -r MSVC1400-SP1/patches/ MSVC1400-SP1/
``` 

Without this patch, `mt.exe` may crash even though the compilation finishes fine.

---

### 2. Create a symbolic link to the original game folder

From within wine, run the following command:

```bash
softlink.bat
```

The script will ask for the full path to your Stronghold Crusader installation directory.

After the link is created, a folder named `_original` will appear in the repository root.

> This script may require administrator privileges to be able to create the symbolic link

Alternatively, copy the game folder as `_original` into the project root.

---

### 3. Set up the Python environment for binary comparison

To set up the binary comparison tools, run:

```bash
python -m venv --prompt reccmp reccmp/dll/.venv
source reccmp/dll/.venv/bin/activate
python -m pip install -r reccmp/dll/requirements.txt
```

Exit and launch a new bash shell to have `reccmp-reccmp` in your PATH.

> In the future, if you want to setup comparison of the reimplemented executable refer to `reccmp/exe` 

---

## Verifying the Setup

If **both** commands complete successfully, your development environment is ready and you can start working on OpenSHC.

### 1. Build the project

From the `OpenSHC` directory, run in a wine cmd prompt (`wine cmd`):

```bash
build.bat RelWithDebInfo OpenSHC.dll
```

---

### 2. Run binary comparison

This verifies byte-level accuracy between the reimplementation and the original binary (run from Linux bash not Wine, assuming you are in the right environment: `source reccmp/dll/.venv/bin/activate`):

```bash
pushd reccmp/dll/ # or use cd if you plan on staying in that directory
reccmp-reccmp --target STRONGHOLDCRUSADER
popd # or stay in this directory
```

> Tip: use `reccmp/dll/run reccmp-reccmp --target STRONGHOLDCRUSADER --verbose <hex address of function>` to investigate code byte mismatches.

---
