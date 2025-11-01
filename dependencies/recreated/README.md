# Recreated Dependencies

This folder contains headers and library files for dependencies of the original game that we do not possess the sources for.

To archive this, the following approaches are used:

### Header Files

The header files are created using reverse engineering, since the general type information is lost.
The files may not contain a mapping for all functions available. The goal is to provide them at least for all functions used by the game.

### Library Files

It is possible to create import LIB-files using the DLLs. For this, the following steps need to be performed with an active dev-environment.

1.  Export the exports:  
`dumpbin /exports MyLib.dll > MyLib.def`
2. Clean up the .def-file:  
    ```
    LIBRARY MyLib
    EXPORTS
        AddNumbers
        MultiplyNumbers
    ```
3. Create the .lib-file:  
`lib /def:MyLib.def /out:MyLib.lib /machine:x86`
