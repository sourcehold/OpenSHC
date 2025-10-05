# Demo setup


## Prerequisites
1. VS 2022 with CMake
### 2. reccmp for binary comparison
```sh
 python -m pip install -r requirements.txt
```

### 3. MSVC1400 for byte-accurate builds
```sh
git clone https://github.com/sourcehold/MSVC1400
```
This also requires NET Framework 3.5 which can be easily installed on Windows 11 by running mt.exe (from MSVC1400 repo), Windows 11 will ask to install the right version.


## Usage
1. Open a developer command prompt VS 2022
2. Navigate to this project folder
3. Invoke vsvars32-portable.bat from the MSVC1400 in the developer command prompt session. Check with `where cl.exe` to see if it was succesful: cl.exe and link.exe are supposed to be executed from your MSVC1400 folder. `where cmake` should point to your VS 2022 installation.
4. Execute build.bat:
```sh
build.bat RelWithDebInfo
```
5. Compare a function byte by byte to check compilation:
```sh
reccmp-reccmp --target STRONGHOLDCRUSADER --verbose 0x401000
```

## How it works
We use CMake to produce NMake files and then make the Visual Studio 2005 software (MSVC1400) build using those nmake files.
