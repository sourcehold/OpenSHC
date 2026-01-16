## Workflow

This document outlines the process for reimplementing the game through reverse engineering and bytecode matching.

### Overview

The workflow involves extracting function signatures and decompiled code from Ghidra, then iteratively refining the C++ implementation until the compiled bytecode matches the original game binary at 90% or higher accuracy.

### Prerequisites

- Ghidra and access to the decompilation, in order to do a SARIF export of the ghidra repo.
- ghidra-skink tool (github.com/gynt/ghidra-skink) to convert SARIF to C++ header files
- OpenSHC project repository (github.com/sourcehold/OpenSHC)
- MSVC1400 (Visual Studio 2005) compiler (included in OpenSHC)
- reccmp-reccmp bytecode comparison tool (python package)

### Workflow Steps

#### 1. Export Ghidra Project to SARIF Format

Begin by exporting your analyzed Ghidra project to SARIF (Static Analysis Results Interchange Format).

In Ghidra, navigate to the export options and select SARIF as the output format. This file will contain all the structural information about the binary, including function definitions, data types, and memory layout.

This export is redone everytime the Ghidra project updates.

#### 2. Convert SARIF to C++ Header Files

Use the ghidra-skink tool to transform the SARIF export into usable C++ header files.

Run ghidra-skink with your SARIF file as input. This tool will generate header files containing function declarations, structure definitions, type definitions, and other necessary declarations extracted from the reverse-engineered binary. These headers provide the scaffolding for the reimplementation: an interface to the original exe.

#### 3. Export Decompiled Functions

For each function in the binary, export Ghidra's decompiled C code to separate .cpp files.

In Ghidra's decompiler view, export each function individually to its own .cpp file. Convert the function's namespace to a file path. This step creates the initial reimplementation starting point, though the decompiled code will require significant refinement.

This task can be semi-automated using a PyGhidra script which provides an API endpoint to fetch a decompiled function with refinements to make it work better with the C++ header files.

#### 4. Refine Decompiled Code

Select a function to work on and adapt the decompiled code to work with the generated header files.

This step involves fixing Ghidra's special helper functions, fixing any decompilation artifacts or errors, and ensuring the code compiles with the MSVC1400 toolchain. Start with simpler, leaf-node functions that have fewer dependencies.

#### 5. Integrate and Compile

Add the refined .cpp file to the CMake build configuration which compiles the project using MSVC1400.

We use MSVC1400 specifically, as the exact compiler version affects bytecode generation. The compilation must succeed before proceeding to comparison.

#### 6. Compare Bytecode

Use the reccmp-reccmp tool to compare the newly compiled bytecode against the original game binary.

Run reccmp-reccmp with both the original binary and your compiled binary as inputs, focusing on the specific function you've reimplemented. The tool will provide a percentage match and identify where discrepancies occur in the bytecode.

#### 7. Resolve Discrepancies

Analyze the bytecode differences and modify the C++ code to improve the match.

Common sources of discrepancies include source code lines being in a different order, compiler optimization differences, incorrect variable types or qualifications (for example, `jge` vs `jg` is produced by `>=` versus `>`, while `jl` is used for signed values and `jb` is used for unsigned values.), wrong evaluation order in expressions (`a > 0` versus `0 < a`), missing or extra casts, and structural differences in control flow (repeated code lines were reduced to a single line). Make targeted adjustments to the C++ code based on the comparison results.

#### 8. Iterate Until Sufficient Match

Repeat steps 5 through 7 until the bytecode match reaches 100%. 

If progress is stuck after several tries, document any remaining discrepancies that cannot be resolved, as these may be acceptable artifacts such as optimizations.

Document the solutions that improved accuracy in a living document describing what source code change produced the desired byte code instructions. Describe in such a way that it becomes searchable later.

#### 9. Process All Functions

Return to step 4 and repeat the process for each remaining function until the entire game is reimplemented.

Work through all functions in the binary. Track your progress and maintain a list of completed, in-progress, and pending functions. Prefereably go function-by-function. Functions that call other functions should generally be implemented after their dependencies to minimize rework.

After reimplementing multiple functions touching the same variables in memory, you may notice wrongly defined variables (e.g. `unsigned int` versus `int`). Document what should be changed in the Ghidra respository and include this information in a new Pull Request associated with your reimplemented functions.

#### Strategic decisions

**Maintain version control:** Older compilers are infamous for having random entropy included in a build. We expect later additions to have complex effects such as optimizations on previous reimplemented functions. Commit each successfully matched function to your version control system separately with clear commit messages indicating the function name and match percentage.

**Document unusual patterns:** Keep notes on any non-obvious implementation details or compiler quirks you discover during the process in the living document.

**Test incrementally:** In case of non-100% matches, test the code where possible. In other words test the game functionality as you implement functions without achieving 100% to catch logical errors that might not be obvious from bytecode comparison.

**Prioritize strategically:** Consider implementing critical game systems first to enable earlier functional testing, even if some auxiliary functions remain incomplete.

**Collaborate on difficult functions:** Some functions may be particularly challenging to match; consider sharing these with other contributors who may spot optimizations or patterns you've missed.

#### Troubleshooting

If you cannot achieve 90% match after extensive iteration, consider whether you're using the exact compiler version and flags that the original developers used, whether there are inlined functions that need to be marked appropriately, or whether aggressive compiler optimizations are creating insurmountable differences. In rare cases, it might be acceptable to document and postpone the function, if the function is demonstrably correct through testing.
