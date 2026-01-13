# OpenSHC
An open source re-implementation of Stronghold Crusader 1. The beloved Castle Building, Real Time Strategy, and Simulation game remastered.

## Usage

### Download and Install
This reimplementation requires you to own a legal copy of the original Stronghold Crusader game from Firefly Studios.

The current method of installation is via the [Unofficial Crusader Patch](https://github.com/UnofficialCrusaderPatch/UnofficialCrusaderPatch). Make sure to set that up first.

0. Set up the Unofficial Crusader Patch.
1. Download the latest release of the reimplementation from the Releases page of this repo.
2. Launch the GUI from the Unofficial Crusader Patch.
3. Drag and drop the zip file unto your open UCP3 GUI, or manually move the zip file into the `ucp/modules` folder inside your game folder.
4. Reload the UCP3 GUI and activate the module.
5. Disable Security in the Launch tab of the GUI.
5. Launch the game!

Note that the goal is to recreate the game. So if there are no changes compared to vanilla, then it is exactly like intended. 

### Help
Raise an issue here on GitHub to receive support. Or visit the [Discord](https://discord.gg/27W68ZaFT4) server.

## Contribute
The development of this reimplementation is a stepwise process. All developers are welcome to contribute.

### Approach
The development of this reimplementation primarily focuses on reimplementing functions and data structures of the original game.
The game 1.41 Latin version of the Stronghold Crusader executable serves as the reference point (SHA hash: 012E9D55DAC04B23ED9A334C975D3A5B6287020B).
To achieve this, a combination approach is used. The code has mechanisms in place to allow a compilation to both and executable and a DLL.
The DLL is meant to be loaded by the UCP and only replace certain functions, while other calls would call into the games executable. This allows to reimplement one function after the other while still maintaining a runnable game.

We use [reccmp](https://github.com/isledecomp/reccmp) to verify compatibility of reimplemented code and the original game.

Because the original game was compiled using an old compiler, you have to compile it using [this compiler](https://github.com/sourcehold/MSVC1400), which is included in the repository via a submodule.

### Prerequisites
1. Stronghold Crusader 1.41 Latin. The Steam version is the easiest one to get, but any patched version will do. Make sure the installation uses a Latin version (English, German, etc).
2. CMake with the minimum version defined in the [CMakeLists.txt](CMakeLists.txt).
3. [Python3](https://www.python.org/)
4. A way to execute `clang-format`
5. (Recommended) An IDE with CMake integration. The repository has been optimized for Visual Studio Code using the [Microsoft C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack).

### Setup
1. Clone the repository. Make sure to also pull the submodules to have the compiler included:
    ```sh
    git clone --recursive https://github.com/sourcehold/OpenSHC.git
    ```
    - Should NET Framework 3.5 be required, it can be easily installed on Windows 11 by running `mt.exe` (from the MSVC1400 repo), Windows 11 will ask to install the right version.
2. Create a softlink to the original game executable with the name `_original` by running [softlink.bat](softlink.bat). It will request the full path to the game folder.
3. Setup the needed Python environment to run `reccmp` for binary comparison by running [setup.bat](reccmp/setup.bat) in the reccmp folder.

### Development
The build can be run using the dev tools of the preferred IDE or via the build scripts. Regardless, a CMake installation is required.

Visual Studio Code with the proper extensions only needs to open the folder and the targets can be chosen in the "CMake" menu.
Additionally, it configures format-on-save and a debug target for the UCP3.

If the scripts are preferred, the following triggers a build using the scripts:
1. Open a terminal. If the Visual Studio CMake version is used, it needs to be the CMD developer command prompt.
2. Navigate to this project folder
3. Execute build.bat:
    ```sh
    build.bat RelWithDebInfo
    ```
4. Compare a function byte by byte to check compilation:
    ```sh
    reccmp/run reccmp-reccmp --target STRONGHOLDCRUSADER --verbose 0x401000
    ```

Note that any code needs to be formatted properly using the provided `clang-format`. The way to do so it up to the developer. Many IDEs support it out of the box.

Should any files be added to the source code in `src/core` or the ucp files in `ucp`, the cmake script [create-include-lists.cmake](create-include-lists.cmake) needs to be rerun and the changed list files need to be committed.

#### Manual configuration
The file `build.bat` exists for convenience. If you want more control, you can specify the following cmake options.

##### Output folder of dll
Use `cmake --preset RelWithDebInfo -D OPEN_SHC_DLL_DEST=.\build-RelWithDebInfo\dll` to specify the destination folder for the .dll and .pdb files in favor of the default.

Note this will be set even if you remove the `-D` option later. To actually clear this configuration, use `cmake --preset RelWithDebInfo --refresh` (cmake 3.24 or later).

##### Building
Build using `cmake --build --preset RelWithDebInfo --target OpenSHC.dll`
