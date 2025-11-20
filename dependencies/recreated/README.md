# Recreated Dependencies

This folder contains headers and library files for dependencies of the original game that we do not possess the sources for.

To archive this, the following approaches are used:

### Header Files

The header files are created using reverse engineering and general research, since the general type information is lost.
The files may not contain a mapping for all functions available. The goal is to provide them at least for all functions used by the game.

### Library Files

It is possible to create import LIB-files using the DLLs. However, it is not easily possible to provide the needed files by hand.
Instead, utilities are used:

* [gendef](https://www.mingw-w64.org/tools/gendef/) to generate the .def-file
* [dlltool](https://sourceware.org/binutils/docs/binutils/dlltool.html) to create the .lib-file

Both can for example be obtained via MinGW. **The x86 version needs to be present, since the 32bit version of libtool is required.**

To create a lib from a dll, perform the following steps:

1.  Create the .def-file:  
`gendef MyLib.dll`
    - This will generate `MyLib.def`.
2. Create the .lib-file:  
`dlltool -m i386 -k -d binkw32.def -l binkw32.lib`  
    - Make sure that the correct version of dlltool is used. If both the x86 and the x64 version are present, the PATH is most likely set to the x64 version. In this case, the path to the x86 version needs to be explicitly specified.
    - `-k` is used based on the info in the generated .def.
