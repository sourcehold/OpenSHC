# Import tools

The tools listed in this directory are for importing a Ghidra-SARIF file into src/OpenSHC as C++ header files.

## Usage

0. Install `ghidra-skink`:

```py
python -m pip install -r requirements.txt
```

1. Export Data, Functions, and Symbols from Ghidra to a .sarif file.
2. Execute the following from PowerShell to cleanly convert the .sarif file into header files:

```pwsh
 & .\tools\import\reimport-ghidra.ps1 -ClearCache $true -OverwriteAll $true -Sarif "path/to/sarif/file.sarif
```

> By default, all .hpp files are backed up to the tmp\backup\ folder. When the .sarif file has not changed between calls of this script, use `-ClearCache $false` to speed up the conversion.
