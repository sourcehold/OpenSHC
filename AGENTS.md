# OpenSHC - AI Agent Guide

## Overview

OpenSHC is an open-source reimplementation of **Stronghold Crusader 1.41**.

The project builds as a DLL that hooks into the original game, progressively replacing original functions with native C++ implementations. The long-term goal is a complete, maintainable, binary-compatible reimplementation.

## Repository Layout

```text
src/
    OpenSHC/       Reimplemented game code
    core/          Runtime infrastructure
    precomp/       Shared headers and compile infrastructure
    symbols/       Original symbol declarations

tools/
    mcp/           MCP server and Ghidra integration
    import/        Ghidra import and synchronization utilities
    reimplementation-control/
                   Project maintenance scripts

reccmp/            Binary comparison tooling

dependencies/      Third-party libraries

status/            Address lists and project progress
```

## Build

- Build system: **CMake**
- Compiler: **MSVC (x86)**

A compatible MSVC toolchain (`MSVC1400-SP1`) is included for consistent code generation. It corresponds to **Visual Studio 2005 SP1**.

Building requires an original **Stronghold Crusader 1.41** installation linked through `_original/`.

## Development Principles

OpenSHC is both a software project and a reverse-engineering effort.

Prioritize:

- correct game behaviour
- binary compatibility
- maintainable C++

Decompiler output, imported symbols, and reconstructed types are valuable references, but are not always authoritative.

Preserve the existing project structure and coding style. Avoid architectural changes or refactoring that alter the existing file and directory structure.

When reimplementing a function, first inspect neighboring implementations and established project patterns. Use decompiler output as a reference, but do not rely on it as the only source of truth.

The C++ level and style is C++98/C++03. Do not use features and structures of C++11 or later.

## Reimplementation Structure

Function and struct resolvers are used as proxies in place of the original game functions and structs.

Reimplementation code interacts with resolvers rather than directly referencing the original symbols. Address identity mismatches are expected when resolvers are inactive and use the original game's addresses.

The following files are primarily generated and should only be modified when explicitly requested:

- `.hpp` files mostly contain generated headers per namespace or class.
- `.hpp` files in `src/OpenSHC/Globals` contain struct resolvers.
- `.func.hpp` files contain function resolvers for functions belonging to a namespace or class.

Implementation code belongs in `.cpp` files:

- Files are named after the function or function group they implement.
- Files are placed in a folder matching the namespace or class of the corresponding header.

## Development Tools

### Implementation Cheat Sheet

The [Implementation Cheat Sheet](IMPLEMENTATION_CHEAT_SHEET.md) is a reference for patterns and oddities of the compiler that are found during the reimplementation process.
Scan this document if you are instructed to reimplement a function.

### MCP Server (`tools/mcp`)

Provides project-specific utilities including:

- retrieving Ghidra decompilations
- compiling individual functions
- comparing generated assembly
- updating local source lists

### Ghidra Import (`tools/import`)

Imports and synchronizes Ghidra-exported data.

### Reimplementation Control (`tools/reimplementation-control`)

Scripts for enabling implementations and maintaining project state.

### Reimplementation Control (`tools/reimplementation-helper`)

Scripts for supporting implementation. Usually already integrated into skills.

### Batch Helpers (`tools/reimplementation-helper/batch`)

Python scripts for working on every function listed in `cmake/openshc-sources.txt.local` at once (see its README):
quiet builds, `/Zs` syntax checks, a reccmp report (match %, normalized % ignoring call targets, snapshots, compact diffs),
showing and splicing many function bodies, one progress commit per changed function, and repairing sources after
`*_Func` namespace refactors. Prefer them over ad-hoc scripts when a task spans many functions.

To pick the next target, `rank_functions.py` orders by lines x (1 - match) rather than by percentage, and
`scan_dispatch.py` lists every function whose dispatch form disagrees with the original (a jump table on one side and an
if/else-if chain on the other), with `scan_chains.py` finding the chains to convert. `try_styles.py` compiles and
measures several hand-written variants of one function and keeps the best, which is the only reliable way to settle a
style question - see the note on unpredictable styles below. `declare_at_use.py`, `decast.py`, `deparen.py` and
`undiv.py` undo decompiler artefacts across a whole selection; run `test_deparen.py` and `test_undiv.py` after
touching the precedence table or the division patterns those two rely on.

The rewriting scripts take a path filter and default to a dry run. Read the diff before building, then run
`syntax_check.py` on what you touched: reviewing a diff catches a wrong transformation but not a rewrite that leaves
the surrounding text unparseable, and `/Zs` finds that in seconds instead of a full build.

**`build.bat` exits 0 even when compilation failed**, which leaves the previous DLL and the previous `diff.json` in
place, so every reccmp number then describes the code as it was before the edit. An "unchanged" percentage is the
symptom. `build_quiet.py` now exits non-zero on `BUILD_FAIL` so `build && report` stops, and `load_diff()` warns when a
source file is newer than `diff.json`; `reccmp_report.py` also warns when the last run covers only part of the build
list, which is what `try_styles.py` leaves behind while it narrows the list to one function.

`orig_asm.py NAME` prints the **original** instruction stream of one function from the last reccmp run, rather than the
interleaved diff `reccmp_report.py diff` gives you. Use it when the diff comes back truncated, or when you need the
original's own jump targets and fall-through order to reconstruct control flow. It reads `reccmp/dll/diff.json`, so it
works with no Ghidra connection.

`orig_asm.py NAME --stats` reports the signals that decide *how* a function has to be reimplemented. Check it before
restyling anything large:

- `mov reg, 0` - no compiler materialises zero that way, so that block is handwritten assembly and belongs in an
  `__asm` block rather than C++. Functions are never `__declspec(naked)`: write a normal function, keep the
  compiler-generated statements as C++, and refer to parameters, locals and `this` by name. Prettify offsets with
  MSVC's struct-member asm syntax (`mov esi, dword ptr [eax]TileMapState.ptr_LogicLayer`) - `::` is not parseable in an
  asm operand, so a resolver global cannot be named there. Where the handwritten block reaches a *global* layer rather
  than a `this` field, give it a C++ pointer local and name that local in the asm; the original caches the same bases in
  stack slots anyway, so the inner loop still matches. `mov eax, 0` followed by `mov ax, word ptr [..]` is the giveaway
  in its own right - that is a hand-rolled `movzx`, which the compiler always emits as one instruction.
  Such a block is usually a **macro**: the same instruction stream appears verbatim in several functions and never as a
  call, so it belongs in a hand-written `*Asm.hpp` beside them (`NeighbourFlagsAsm.hpp`, `LinkageNeighbourAsm.hpp`).
  This has been worth ~45 points per function, three times over.
- a frame pointer plus a `this` spill - the original was built without optimisation, **unless the same function also
  reports `mov reg, 0`**. MSVC keeps `ebp` in any function containing an `__asm` block, so for a function with
  handwritten assembly the frame pointer says nothing about the optimisation level: reimplement the handwritten part as
  inline asm and leave the rest at `/O2`. Checking the prologue settles it - values kept in registers across the entry
  tests mean `/O2`. Taking the `/Od` reading instead took `findLinkageBasedPathOrWalkRadius` from 5.1% to 2.8%, where
  the same body without the pragma reaches 49.2%. When it really is `/Od`, add `#pragma optimize(, off)`
  around the function; inline asm alone does not disable optimisation. Then match the reported **frame size** exactly,
  which is usually the single biggest win, because every local displacement shifts otherwise. Merge locals that share a
  slot and reproduce dead stores. At `/Od` prefer a nested `if` over an early `continue` (the original inverts the test
  and jumps to the loop's continue trampoline), and declare locals together at the top of the function.
- a jump table - Ghidra usually renders the dispatch as a call through an unnamed pointer array and drops the arms, so
  rebuild the `switch` from the byte and jump tables instead of restyling the decompiler output.

`diff_triage.py` gives one line per function in the build list and says whether more source work can pay at all: it
flags a `sub esp` frame-size mismatch (`FRAME`), byte-sized stack slots we have and the original does not (`BYTE`), a
cold return block we inline where the original outlines it (`RET`), and the case where only register and stack-slot
*naming* is left (`alloc-only`). Chase a `FRAME` flag with `diff_slots.py NAME`, which lists every `[esp + N]` slot per
side: one extra slot is one local the original does not have, and removing it has been worth 10-30 points.
`diff_jcc.py` finds comparisons whose operator is one strictness step off the original (`jl`/`jle`, `jg`/`jge`) - these
are real off-by-one bugs where Ghidra decompiled the condition wrongly, so confirm a fix by re-running that tool rather
than by the percentage. `diff_types.py` is its counterpart away from comparisons: `movsx` against `movzx` for one field
means the field's signedness is wrong in the generated header, and `add` against `sub` of the same magnitude is a sign
error in a formula - that is how `2400 / n + 40` was caught being `- 40`, which Ghidra had decompiled with the wrong
sign. It carries only those two rules on purpose: a third, "same instruction with a different constant", was tried and
dropped because every hit it produced was a loop-induction stride rather than a constant the source chose.
`reorder_search.py FILE NAME` hill-climbs the match % by reordering independent statements,
which is the only lever left once a function is `alloc-only`; it pays about one move in ten, and mostly where the
statements sit between two calls or on a loop back-edge.

### Binary Comparison (`reccmp`)

Compares generated binaries against the original executable.

## Working on Many Functions

When restyling or improving a large set of functions, work in batches (e.g. per folder) and verify each batch:

0. Switch the global data reimplementations on (the `MACRO_STRUCT_RESOLVER` flag in `src/OpenSHC/Globals/*.hpp`)
   before measuring anything, and never commit those files. With the resolvers inactive, reccmp collapses every
   absolute address to one token, so a `this->` that should be the global instance, and a wrong field offset, both
   look like a match.
1. Save a baseline: `reccmp_report.py --run save base.json`.
2. Rewrite the bodies (`show_functions.py` -> edit -> `splice_functions.py`), then `syntax_check.py` and `build_quiet.py`.
3. Compare with `reccmp_report.py --run cmp base.json`; revert or rework every `WORSE` function and inspect the rest with `diff`.
4. Commit with `commit_progress_batch.py` (100% "Reimplemented" when only call targets differ, otherwise the % with a short blocker remark).
   Field and parameter type changes to generated headers go in a commit of their own, separate from the `.cpp` work.

Replace a function body whole. Do not patch one by slicing its existing text: a scripted edit that cuts the body at
some marker and splices a fragment back silently loses brace balance, and `clang-format` then reflows the damage into
something that still looks plausible - a `do { ... } while (cond);` comes back as a bare `while (cond);` with the loop
body detached above it. `syntax_check.py` does catch it, but the rewrite is wasted and the cause is not obvious from
the error. This is why `splice_functions.py` replaces whole bodies; when editing by hand or from your own script, emit
the function from its signature through its closing brace, keeping the `// FUNCTION:` line above it untouched.

Style expected of reimplemented code:

- Declare variables where they are first used; access fields repeatedly instead of copying them into locals
  (the compiler created the locals), unless the diff shows the original really used a local. Whether naming a
  repeatedly read field helps is not predictable and has to be measured per function: it gained 18% in one function
  where the value fed distance arithmetic and lost 12% in another where it fed a chain of `== constant` tests, which
  MSVC compiles against the memory operand directly. The same applies to other style choices - reusing one pointer for
  two rows helped one function and hurt its near-identical neighbour. Use `try_styles.py` rather than reasoning about it.
- Use `for` loops (loop variable declared in the `for`), early returns instead of nested if/else, no `goto`,
  no pointer variables walking over arrays or structs, named fields and enum constants instead of offsets and magic numbers.
- Never change the `// FUNCTION:` address line; keep generated headers untouched unless asked.
- Write sources as UTF-8 with LF line endings.

When removing the decompiler's `goto`s, check how many predecessors the target block has. A `LAB_*` reached from
several places has to be **duplicated** into each path; dropping it instead still compiles and is silent. Three such
bugs sat in one function (`processEntityDamageToUnit`): a damage value never assigned so the variable still held an
unrelated height, a `break` left outside its `if` that made six `switch` arms unreachable, and a `case` that fell out
of the switch leaving the value it should have set uninitialised. Fixing them was also worth 7.7% of match, so a
suspicious dead store is worth decompiling for rather than deleting. Note this is the opposite of the duplicate-tail
pattern below, where our shared block should have been two separate branches - check the predecessor count either way.

Duplicating a `LAB_*` is correct C++ but not automatically a better match, so **measure every `goto` removal**. A
`goto` in the decompiler output usually marks a block the original compiler emitted once and jumped to, and writing
the block out twice makes MSVC emit it twice: duplicating the single shared tail in
`setClimbBasedOnClosestClimbData` - two `if` arms that set a coordinate pair and then share the distance test - was
semantically identical and cost **35 points**. Keep the `goto` where the measurement says the original shared the
block, and record that in the commit remark rather than trading match for style.

Diff patterns that were reliable (more in the cheat sheet):

- Absolute `DAT_*` addresses in the original asm where the source uses `this->` mean the original accessed the global instance.
- Signed `jl/jge` vs our unsigned `jb/jae` on `undefined4`/`uint` fields: compare through `(int)`.
- `cmp x, N; ja` means `<= N`; write the literal the asm shows.
- `mov r, [x]; sub r, 1; je` inside a loop is a `switch` on `x`.
- A tail call to the same callee from our code but a jump back to a shared block in the original means separate
  `if` branches with identical bodies, not a combined condition.
- Callee-saved registers reused after a call without reload (`ecx`/`edx`) indicate LTCG (`cmake/compiler-flags-gl.txt`),
  not a source difference.
- A mismatching argument count or `ret N` usually means the generated header is wrong; report it instead of working around it.
- Diffs can reveal real bugs in existing reimplementations (wrong constants, wrong strides); fix those.
- `(-(uint)(c) & MASK) + BASE` in the decompiler output is a conditional it has already turned into mask-and-add:
  it is `c ? BASE + MASK : BASE`. Writing the conditional out recovers the same instructions and stops the constants
  being unreadable - `(-(uint)(d != 1) & 0xffffffce) + 200` is `d == 1 ? 200 : 150`.
- `(x + (x >> 0x1f & 7U)) >> 3` is a signed division by 8, not a shift: shifting alone rounds towards negative
  infinity, so the compiler biases the value first and the decompiler reports the bias. Any mask `2^k - 1` paired
  with a shift of `k` is `x / 2^k`. Writing the division back recovers the same instructions and has been worth a
  great deal - 22 sites in one namespace, up to +22% on a single function (`undiv.py` rewrites them). The bias also
  proves the dividend is signed, so a surrounding `(int)` cast is redundant once the division is back. Measure
  anyway: one site out of 22 came out 0.1% worse and kept the shift.
- `v = x & 0x8000000f;` followed by `if ((int)v < 0) v = (v - 1 | 0xfffffff0) + 1;` is `v = x % 16` - the low bits and
  the sign bit masked together, then the negative case repaired (`unmod.py`). The mask's low bits and the `|` constant
  always complement each other. The repair proves the operand is signed, so the dividend has to stay signed in our
  source too: the decompiler's `uint` locals and its `+ 4U` make the sum unsigned, and an unsigned `%` compiles to a
  bare `and` with no repair, which loses the match instead of gaining it.
- `piVar1 = &x.field; *piVar1 = *piVar1 + 1;` is `x.field = x.field + 1` (`unptr.py`), worth 1.2% over 60 sites in one
  function. Only rewrite it when the store immediately follows the pointer: a pointer freezes the address while the
  field form re-evaluates the index, so with a call or a write to the index in between the two forms differ.
- Our `movzx` against the original's `movsx` on a `ushort` layer (`PathConnectionLayer`) means the original cast the
  read: `dword x = (short)layer[i]`, one `movsx`. Declaring the local `short` does not do it - the signedness comes
  from the cast on the array access, not from the destination.
- `jmp dword ptr [reg*4 + table]` on one side only is a dispatch-form mismatch: a `switch` over contiguous values
  becomes a jump table, an if/else-if chain becomes compares. Both directions have been worth several percent
  (`scan_dispatch.py` finds them). Handing some of a switch's values to `default:` and re-testing them with an `if`
  drops them out of the table, so give every value its own `case` and lift a shared tail out behind a flag instead.
- `x < 1` compiles to `cmp x, 1; jl` but the original usually shows `test x, x; jle`, i.e. `x <= 0`. The two are
  identical for signed and unsigned alike; write the form the asm shows.
- A range's upper bound is half-open when the original ends it with `jge` and inclusive when it ends with `jg`.
  Writing `<= N-1` where the original has `< N` is a real off-by-one whenever the bound is a player or slot count -
  `processSingleTimeTick` had five, each calling a per-player routine one index out of range.
- Trust the asm over the decompilation for constants and their sign. Ghidra rendered `2400 / n + 40` where the binary
  has `sub eax, 0x28`, so the formula is `- 40`; the function reached 100% once corrected (`diff_types.py` finds these).
  A `(longlong)` in a Ghidra division is usually spurious too - it emits `_alldiv` where the original has a plain `idiv`.
- MSVC1400 at `/O2` never unrolls a loop, so a body repeated N times in the asm means the source was written out N
  times. A plain loop where the original is unrolled has cost 80 points on its own.
- A flag stored with `mov dword ptr [..], 0/1` is an `int`, not a `bool`, which stores a byte.

## Agent Skills

Task-specific guidance is available under `.agents/skills/`.

When a relevant skill exists, prefer it over this document, as it contains more detailed workflows and repository-specific guidance.

## Agent Maintenance

If you discover undocumented conventions, missing workflows, or repeated guidance, suggest updates to this guide or the relevant skill.
