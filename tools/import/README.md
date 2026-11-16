# Import tools

The tools listed in this directory are for importing a Ghidra program into src/OpenSHC as C++ header files.

## Usage

0. Install `ghidra-skink` and pyghidra, and set `GHIDRA_INSTALL_DIR` to your Ghidra installation (needed by pyghidra):

```py
python -m pip install -r requirements.txt
python -m pip install pyghidra
```

1. Export the program from Ghidra as a .gzf (File > Export Program..., format "Ghidra Zip File") to `Stronghold Crusader.exe.gzf`.
2. Execute the following from PowerShell to cleanly convert the .gzf file into header files:

```pwsh
 & .\tools\import\reimport-ghidra.ps1 -OverwriteAll $true
```

Use `-Gzf "path/to/gzf/file.gzf"` to read a different .gzf file.

> By default, all .hpp files are backed up to the tmp\backup\ folder.

## Usage with a .sarif

The headers can also be generated from a SARIF export of the program, which is slower (about ten minutes instead of
about half a minute) but gives the same header files.

1. Export Data, Functions, and Symbols from Ghidra to a .sarif file, or generate it from the .gzf with
   `python .\tools\import\gzftosarif.py --gzf "Stronghold Crusader.exe.gzf" --sarif "Stronghold Crusader.exe.sarif"`.
2. Execute the following from PowerShell:

```pwsh
 & .\tools\import\reimport-ghidra.ps1 -ClearCache $true -OverwriteAll $true -Sarif "path/to/sarif/file.sarif"
```

> When the .sarif file has not changed between calls of this script, use `-ClearCache $false` to speed up the conversion.
