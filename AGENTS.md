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
list, which is what `try_styles.py` leaves behind while it narrows the list to one function. `try_styles.py` now
restores the list *and* rebuilds before exiting, because restoring the list alone is not enough - the DLL is still
the narrowed one, so `diff.json` keeps reporting a single function at the last variant's score and `--run` cannot
repair it. That rebuild costs a few minutes per invocation and is worth paying.

`try_styles.py` reports four decimals, and its tie test is exact. It used to parse the one-decimal percentage
`reccmp_report.py` prints, so anything sharing a first decimal compared as a tie - which is how a variant 0.02
points *below* its baseline got kept as "identical, so pick the readable one". Treat a tie from an older run as
unverified.

`orig_asm.py NAME` prints the **original** instruction stream of one function from the last reccmp run, rather than the
interleaved diff `reccmp_report.py diff` gives you. Use it when the diff comes back truncated, or when you need the
original's own jump targets and fall-through order to reconstruct control flow. It reads `reccmp/dll/diff.json`, so it
works with no Ghidra connection.

reccmp cuts the original's stream at the length of *our* function, so when ours is shorter the original's tail is
simply missing from the diff (it reads as "the original has no `ret`"). `quick_diff.py FILE.cpp` disassembles the whole
original function from `_original/` and diffs it against a `/FA` compile of that one file in about six seconds, with
no link and no reccmp run. Use it to try source variants - it is what broke the `AI::AICState` plateau that
`try_styles.py` at several minutes per variant had declared allocator-bound - and confirm the result with reccmp.

`orig_asm.py NAME --stats` reports the signals that decide *how* a function has to be reimplemented. Check it before
restyling anything large:

- `mov reg, 0` - no compiler materialises zero that way, so that block is handwritten assembly and belongs in an
  `__asm` block rather than C++. Functions are never `__declspec(naked)`: write a normal function, keep the
  compiler-generated statements as C++, and refer to parameters, locals and `this` by name. Prettify offsets with
  MSVC's struct-member asm syntax (`mov esi, dword ptr [eax]TileMapState.ptr_LogicLayer`) - `::` is not parseable in an
  asm operand, so a resolver global cannot be named there.
- a frame pointer plus a `this` spill - the original was built without optimisation. Add `#pragma optimize(, off)`
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

**Check the struct resolver flags before trusting any comparison.** The global data
reimplementations are enabled by flipping the boolean in every `MACRO_STRUCT_RESOLVER` in
`src/OpenSHC/Globals/*.hpp`, which is deliberately never committed, so a rebase, a fresh clone or a
`git checkout` silently turns them all off. With them off, absolute addresses stop being
distinguishable and the raw match drops across the whole namespace while the normalized match barely
moves - which reads exactly like a catastrophic self-inflicted regression. One rebase cost ~3 points
of namespace average this way, and a snapshot taken on one side of that change cannot be compared
with anything measured on the other. `tools/reimplementation-control/enable_reimplemented_data.py`
turns them back on; `git checkout -- src/OpenSHC/Globals/` turns them off again.

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
  The early-return preference has one known exception, still tentative - see the note on arms sharing a tail among the
  diff patterns below.
- Never change the `// FUNCTION:` address line; keep generated headers untouched unless asked.
- Write sources as UTF-8 with LF line endings.

When removing the decompiler's `goto`s, check how many predecessors the target block has. A `LAB_*` reached from
several places has to be **duplicated** into each path; dropping it instead still compiles and is silent. Three such
bugs sat in one function (`processEntityDamageToUnit`): a damage value never assigned so the variable still held an
unrelated height, a `break` left outside its `if` that made six `switch` arms unreachable, and a `case` that fell out
of the switch leaving the value it should have set uninitialised. Fixing them was also worth 7.7% of match, so a
suspicious dead store is worth decompiling for rather than deleting. Note this is the opposite of the duplicate-tail
pattern below, where our shared block should have been two separate branches - check the predecessor count either way.

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
- Instruction order is not statement order: the compiler schedules freely inside a boundary, so a long run of
  independent stores into one object says nothing about the order the fields were assigned in the original source
  (see the cheat sheet's *Statement Order*). Reordering the body to follow the asm makes the match worse.
- Diffs can reveal real bugs in existing reimplementations (wrong constants, wrong strides); fix those.
- An `if (cond) {}` with an empty body is a `goto` the import dropped, and it is almost always a *loop or
  function exit*. Thirteen sat in `Map::Units::TroopValueState`, six of them leaving a `do { } while (true);`
  that never terminates. Read the original's jump target with `orig_asm.py NAME` - a jump past the loop's
  back edge is `break`, a jump into the epilogue is `return` - and fix the exit *before* restyling anything
  else: `placeTunnelForEveryTunneler` went 32% -> 52% from three `return`s alone, while the same function
  rewritten structurally first went *down*. Where the correct exit costs match because the original shares
  one epilogue and we need two, keep the fix and say so in the commit remark.
- A literal game address (`while ((int)p < 0x17802b4)`, `*(byte*)(tile + 0x1ee2998)`) is the original's global,
  which `resolve_address.py` turns into `DAT_X::instance.field[i]`. It is only correct while that struct's
  reimplementation is off, because an enabled resolver puts the data in our own object, so these are latent
  bugs and worth replacing. Replacing an *array base* is free or better; replacing a *loop bound* is not -
  a typed pointer bound (`p < &tribes[1251]`) re-anchors the walk and cost 5-11 points in three functions,
  where converting the whole loop to an index over `tribes[t]` gained instead.
- **Where a field read sits relative to a call or a test is worth more than almost anything else.**
  The decompiler hoists reads to the top of a block; the original reads them where they are used, and
  `quick_styles.py` settles it in seconds per variant. Moving one read down past a call took
  `recountTotalTroopValue` 27.7% -> 49.5% and `collectArcherUnitsByLocation` 49.4% -> 61.5%; moving one
  down past two threshold tests took `queueOilThrowForIdleArchers` 70.7% -> 100%. The same lever runs the
  other way for an argument subexpression inside a short-circuit chain, which the original computed
  *before* the test: hoisting the `PathConnectionLayer` lookup out of the `&&` took
  `assignBehaviorTypeToNearbyTribes` 46.6% -> 68.0%. Read which side of the branch the original's address
  arithmetic falls on and follow it.
- `if (x < N) { if (x == N) { ... } ... }` is a three-way test the decompiler flattened wrongly: the inner
  arm is unreachable, so whatever it does never happens. The original tests `> N`, then `== N`, then falls
  through to the rest. Rebuild it as `if (x < N) { rest } else if (x == N) { arm } else { high }` - the
  fall-through arm has to stay first or MSVC lays the blocks out the other way and the match collapses
  (20 points on `updateTribeBehaviorBasedOnBehaviorType`, which is also where the unreachable arm was).
- A `je` in the original against a `jne` of ours after the same compare means the two arms of an
  `if/else` are the other way round: the arm the original falls into is the one it keeps inline, and the
  one it jumps to is the one we should put in the `else`. `scan_arms.py` lists them. Swapping took
  `getPlayerNot1AndHasKeep` 50% -> 100%, `addUnitToNewTribe` 84% -> 100% and
  `aiControlNonSkirmishUnitMovement` 78% -> 98.6% (two swaps plus a tail call), and it is the same lever as
  inverting an `if/else if` chain so its first test matches the original's - `computeAttackWaveTroopComposition`
  gained 11 points from testing `< 10` and taking the lower arm there instead of `9 <` and taking the upper.
  Read the original rather than trusting the hint: the scan pairs branches loosely and one of its five
  suggestions measured worse.
- `pop`s followed by `jmp <callee>` in the original is a tail call, so nothing runs after it. Where the
  decompiler shows that callee in the middle of a function, the original returned there:
  `aiControlNonSkirmishUnitMovement` called `updateAttackInfoTick` and then carried on, where the original
  stops, and fixing it was worth 3.6 points before the arm swaps.
- `expr * 0x177bc` into one of `AttackInfo`'s own `*ValuesArray` members is `playerInfo[player - 1]`:
  the per-player `AttackInfoSubElement` array is one-based, and `AttackInfo`'s named copies of those fields
  are the unused slot 0 at the same relative offsets (delta 0x301C0). Writing
  `playerInfo[playerID - 1].wide2` for `*(int*)((int)wideValuesArray + playerID * 0x177bc + -8)` took seven
  of that namespace's "find the nearest X" functions from 45-78% to exactly 100%, and the negative deltas
  (-0x10, -0xc, -8, -4) are the four scalars declared before each array.
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
- `diff_types.py`'s `EXTEND` hint usually does **not** mean the header is wrong. Every field it flagged across
  `Map::Units::UnitsState` was already correctly signed (`short OrganismLayer`, `short owner`,
  `typedef short UnitTypeShort`). What it detects is a 16-bit load that needs a second instruction to sign-extend,
  where the original does one `movsx`, and that arises three ways with three different fixes. This was the most
  productive seam in that namespace, ten functions and most of a point of namespace average, after hand analysis of
  the same functions had concluded they were allocator-bound:
  - **A local declared `short` (or `ushort`) that holds a field read** - widen it to `int`. The safest of the three:
    it cannot add a memory read, only change the extension width of one that already happens. One such local took
    `resetUnitMovementState` from 85.7% to 95.2% and normalized 100%. 17 of 18 candidates gained.
  - **A byte-sized local** (`diff_triage.py`'s `BYTE` column, nonzero on our side only) - widen it to `int`, worth
    +12 points on `updateUnitFadeAndVisibilityNearStructures` alone. But only when the flag is set from constants:
    one initialised from a `BOOLEnum`-returning call lost 3 points, because `bool x = call()` emits the test that
    normalises the result to 0/1 while `int x = call()` stores it raw, so there the `bool` is load-bearing.
  - **A field read repeatedly with no local at all** - give it one `int` local, but only when the value feeds
    arithmetic, indexing, or a comparison against another variable (+4.7 on `calculateUnitMovementSpeed`). When it
    feeds comparisons against *constants*, leave it alone: MSVC compares against the memory operand directly, and
    introducing the local cost 11.8 points on `playHurtSFXForUnit` and 0.3 on `updateUnits`. This is the
    unpredictable case the style notes above warn about; the `EXTEND` hint plus how the value is used is what makes
    it decidable.
  Signedness is what matters, not width: a `ushort` local widened to `int` zero-extends either way and gained
  nothing. An `EXTEND` on an *array element* is weaker evidence than on a scalar - declaring a `ushort` scratch
  array `short` and dropping fifteen `(short)` read casts was an exact tie.
- `diff_triage.py`'s `FRAME` column is worth checking but, unlike `BYTE`, is not mechanically actionable. Every
  cheap hypothesis for the frame mismatches in `Map::Units::UnitsState` came back an exact tie or worse: local
  declaration order, array element type, widening unsigned locals, and splitting a local the decompiler had reused
  for two values. `diff_slots.py` says the lowest-access extra slot is usually the culprit, so a function whose
  extra slots are all heavily used has genuine live values rather than a stray local, and needs structural
  understanding rather than a rule.
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
- MSVC1400 at `/O2` does unroll small constant-trip loops (`applyAIV`'s 10-iteration unit loop comes out five copies
  wide from a plain `for`), and `!=` as the bound suppresses it - see the cheat sheet. A body repeated N times in the
  asm is therefore not proof that the source wrote it out N times; compile the plain loop first and compare.
- A flag stored with `mov dword ptr [..], 0/1` is an `int`, not a `bool`, which stores a byte.
- Tentative, one clear case so far: where two arms of a condition share a tail, the nested `if/else` shape the
  decompiler emits can beat the early returns the style list above asks for, because it decides *which* arm holds the
  physical copy of the shared block. In `calculateTaxIncomeForPlayer` the original keeps the shared `(tax * 150) / 100`
  in the second arm and jumps forward into it from the first; early returns put the copy in the first arm and made the
  second jump backwards, and switching to nested `if/else` was worth 17 points. Read the original's own jump direction
  with `orig_asm.py NAME` to see which arm should hold it. Treat this as a thing to try, not a rule: the same change
  measured *worse* on `updateCrowding` (all three nested variants lost 9-14 points) and made no difference at all on
  `showPopAndGoldPopup` and `createStatsPopUpEntities`, where every shape tied to the decimal because the gap there is
  the loop base-pointer anchor. `try_styles.py` settles it per function; prefer the early-return form on a tie.

## Agent Skills

Task-specific guidance is available under `.agents/skills/`.

When a relevant skill exists, prefer it over this document, as it contains more detailed workflows and repository-specific guidance.

## Agent Maintenance

If you discover undocumented conventions, missing workflows, or repeated guidance, suggest updates to this guide or the relevant skill.

- **`reccmp_report.py --run` does not build.** It only re-runs reccmp over the DLL that is already
  on disk, so a source edit measured with `--run` alone scores the *previous* build. Run
  `build_quiet.py` (check for `BUILD_OK`) first, every time. A suspiciously bit-identical diff -
  same percentages and the same `(file.cpp:NN)` line numbers as before the edit - is the symptom.

- **Switch-arm source order decides the arm layout, including for a jump-table switch.**
  `playAttackAlarmSound` went 75% -> 100% purely by moving `case 5:` ahead of `case 2/3/4:`, which
  is the order reccmp's printed jump table implies (the arm reached by the lowest `start + N`
  offset comes first in the source). Sort the distinct jump-table offsets, map each back to its
  arm, and lay the arms out in that order.

- **Four identical stores beat one shared store.** Where Ghidra nests a chain of tests as
  `if (a) { x = K; } else { if (b) { x = K; } else { ... } }`, the original often writes each
  failure as its own guard - `if (a) { x = K; goto LAB_tail; }` - repeated per test, with the
  success path falling into a label just before the loop's increments. reccmp shows this as the
  original carrying several copies of the same `mov dword ptr [reg], K` plus a `jmp`, against a
  single copy on our side. `computeSiegeSpotScores` gained 5 points from it (47.4% -> 52.2%);
  rewriting the same block's `!x` tests as signed `(int)x < 1` at the same time *cost* 3, so land
  the restructure on its own and measure before touching the comparisons.

- **`b = a + 1; <call>; a = b;` is one variable, not two.** When a counter is live across a call,
  Ghidra sometimes names the pre-call and post-call halves separately, leaving a copy-back that
  reads as a no-op (`a = b;` on a path where `b` never changed). reccmp shows the original doing
  `add reg, 1` / `mov [esp+N], reg` once and reloading after the call, against our two counters
  shuffling between a register and two slots. Merging them into one variable took
  `assignMacemenAndKnightsNotFromPlayer1ToTribes` from 41.8% to 52.5%. Check that the two really
  are equal at the top of each iteration before merging - initialised together, and every
  assignment to one followed by the copy-back.

- **A store Ghidra invented from a shared constant.** `computeAttackWaveTroopComposition` opened
  with `maxMoatAttackTribes = 6;` although every arm of the chain below assigns that field; the
  original only materialises 6 for the first `cmp`. If reccmp shows a `mov dword ptr [global], reg`
  on our side alone right before a compare against the same constant, and the field is written on
  every path, the assignment is not in the original.

- **`test r8, r8` + `jbe` is `0 < (byte)x`, not `x != '\0'`.** `jbe` after a compare against zero
  means the source tested an *unsigned* value with `<` or `<=`; a `!= 0` test gives `je`/`jne`
  instead. Writing the guard as `if (0 < (byte)cVar1)` is what reproduces it. Five of those plus a
  restored `else` took `decrementTileMap1104` from 79.4% to an exact match.

- **An unconditional store after a conditional one means a dropped `else`.** Ghidra emitted
  `if (off < 80200) { off += 200; } off = 0;` - which makes the increment dead, and our compiler
  duly dropped it, so reccmp showed the original carrying a `cmp`/`jge` we had nothing for. The
  second store belongs in an `else`. Any tail where the decompiler assigns a field it has just
  conditionally updated is worth this check.

- **Loop shape is not reachable from the source.** `pruneStaleArcherPoints` and its two twins walk
  a 199-element array; the original exits on `cmp esi, <end address>` / `jl`, we emit a down-counter
  (`mov edi, 0xc7` / `sub edi, 1` / `jne`), and that single transform is the whole 29% they are
  missing. A `do/while` on the pointer, a `for`, a `while`, `!=` instead of `<`, an index with the
  pointer derived inside, and a hoisted end-pointer local all compile to the *same* down-counter -
  measured, not assumed, on three functions in one build. When several spellings of a loop give a
  bit-identical diff, the remaining difference is the optimiser's and there is nothing left to try.

- **Near-miss constants are comparison encodings, and they are worth sweeping for.** Ghidra prints
  `x < K+1` where the original compiled `x <= K`, and `K-1 < x` where it compiled `K <= x`; the
  reccmp diff shows it as the original's `cmp reg, K` against our `cmp reg, K+-1` on the next line.
  Scan every sub-100 diff for adjacent `-cmp`/`+cmp` pairs whose constants differ by a small
  amount, then rewrite each condition in the original's form. Seven of them in one build lifted six
  functions and cost nothing anywhere. The same scan with the delta restricted to a struct size
  (820 for Tribe, 1168 for Unit) finds loop bounds that are off by one whole element.

- **Comparison operand *order* is visible too, and sweepable the same way.** MSVC emits
  `cmp <left>, <right>` in source order, so `bound <= index` and `index >= bound` - identical in
  meaning - produce opposite operand orders. Scan the diffs for an adjacent `-cmp A, B` / `+cmp B, A`
  pair and rewrite the condition with the original's left-hand side first: the index before its
  bound, the tick before its delay, the cached field before the layer read. Worth 2 points on
  `placeTunnelForEveryTunneler`, 2 on `scanForSiegeTentPoints`, 1.4 on `initializeOrAdvanceAttackWave`.
  It is not universal - 25 flips in `updateTribeBehaviorBasedOnBehaviorType` changed nothing at all,
  because the compiler had already canonicalised those - so measure per function.

- **An inverted `jcc` means the two arms are the wrong way round - scan for it first.** For every
  sub-100 function, pair each `-jcc` in the diff with a `+jcc` within three lines and flag the ones
  whose conditions are exact inverses (`je`/`jne`, `jl`/`jge`, `jg`/`jle`, `ja`/`jbe`). Each hit is
  an `if`/`else` whose arms the original lays out in the other order, or a guard written with the
  opposite sense; rewriting it in the original's sense is usually a few lines and has been the
  single most productive sweep here:

      isLessThanPercentageOfTribesInAttackDying  89.6 -> 100.0   (zero case first, with an else)
      collectArcherUnitsByLocation              61.5 ->  75.9   (mask test positive, arms swapped)
      updateInProgressAttackWave                78.4 ->  84.1   (tent-points arms swapped)
      computeAttackWaveTroopComposition         55.3 ->  60.7   (four wall-scale chains swapped)
      findNearestDiggableMoatPoint              89.2 ->  94.6   ('(int)tile <= -1', giving jg)

  Beware that the sense also encodes signedness and the exact constant: `!x` gives `jne`, `(int)x
  <= 0` gives `jg`, and `(int)x < 1` gives `jge` - three spellings of the same test with three
  different branches. Pick the one the original used.

- **A `(short)` cast written twice in one condition costs a conversion.** `registerSpottedEnemyTile`
  cast `EntityLayer[tile]` from short once for the zero test and again as the array index; the
  compiler emitted `movzx` + `test ax, ax` + a second `movsx`, where the original does a single
  `movsx` into a register it then reuses. Reading it once into an `int` local took that function
  from 81.8% to an exact match. Scan each sub-100 source for the same `(short)expr` appearing twice
  - the declared-`short`-local form of this is the same bug with a different spelling. It does not
  always pay (hoisting `(short)_unitID` in `recomputeAttackInfo` cost 2 points), so measure.

- **Per-block work on a long function: map its counters, not its instructions.** For a function too
  long for reccmp to align (`recomputeAttackInfo`, 981 instructions, ten near-identical per-feature
  blocks), the way in is to find a value each block touches exactly once - here the `gate1`,
  `town1`, `high1`, `arch1`, ... counters - resolve each to its `instance+N` offset from the
  prologue's zero stores, then grep `orig_asm.py NAME --both` for those offsets *in address order*.
  That prints the original's block layout directly:

      people lord gate town high2 arch2 wide hack scale moat

  Ours had the owned-building arm as high2/arch2, town, gate - exactly reversed. `swap_arms.py`
  reorders an `if`/`else` or `if`/`else if` chain in place (it negates the condition, so behaviour
  is unchanged); three calls on the nested chains were worth 2 points.

  **The layout order is not the whole source order, though.** Matching it completely measured
  *worse*: moving `moat` last cost 1.3 and swapping the two outer arms another 2.1, because MSVC
  outlines some of these blocks rather than emitting them where the source puts them. Reorder one
  chain at a time and keep only the chains that measure better.

- **When the two streams are the same length, stop looking for missing code.** `recomputeAttackInfo`
  is 941 instructions against the original's 981, with the same 41 calls in the same order and the
  same addressing idioms - so its 30% is an *alignment* score, not a structural gap: the prologue
  allocates the player offset to a different register and needs one stack slot more, the streams
  desynchronise there, and everything after counts as a mismatch. Things that look like the cause
  and are not (all measured, all reverted): un-caching the second neighbour-gather so the layer
  pointers reload, inlining three single-use height locals, moving the hoisted `ptr_SpecialAreasArray`
  / `ptr_PathConnectionLayer` loads down to their first use, and hoisting a repeated `(short)_unitID`.
  Count both streams before spending a day here.

- **Retry a failed change once the function has moved.** Replacing `this->attackInfo.` with
  `DAT_TroopValueState::instance.attackInfo.` in `initializeOrAdvanceAttackWave` measured *worse*
  early on (54.8% -> 38.2%) and took it from 58.8% to 88.1% later, after the pointer temp and the
  loop bound were fixed. Through `this` every field is a this-relative literal offset that can never
  match the original's absolute addressing, so the change was always right; it just could not show
  while a larger misalignment sat in front of it. When a change you believe in measures worse, note
  it and try it again after the next structural win - and when it still loses, trust the number
  (the same substitution in `scanForSiegeTentPoints` has now lost twice, five points each time).

- **Symbolic loop bounds are not automatically better than Ghidra's literal.** Rewriting
  `(int)p < 0x176238c` as `(int)p < (int)&tribes[1250].owner` reproduces the original's symbolic
  operand but costs a `lea` to re-anchor the walking pointer, and measured worse on
  `placeSiegeTentsAndAssignEngineers`, `recountAttackTroopValue` and
  `sortAttackInfoTribeIDArrayBasedOn` (that last one by 14 points). Check the trip count either
  way - `&tribes[1250]` and the literal are usually count-equivalent, so the literal is not a bug -
  and keep whichever measures better.

- **Verify a jump table's index -> case mapping against the *data* table.** For a sparse switch MSVC
  emits a byte table (value - min -> jump index) alongside the jump table, and reccmp prints both.
  The indices run strictly ascending over the case values that are present, and `default` gets the
  *last* index - not a slot in the middle. I assumed the default sat at index 12 in
  `updateTribeBehaviorBasedOnBehaviorType`, which shifted every case from 0x400 on by one and made
  the derived arm order wrong from position 6 onwards; it still gained 9 points, which is how it
  went unnoticed. Correcting it gained another 7 and made our layout match the original's exactly.
  `arm_layout.py` prints both layouts, so check them rather than trusting the derivation.

- **`arm_sizes.py` turns a big switch into a short worklist.** Differencing consecutive jump-table
  offsets gives each arm's byte size on both sides, so an 800-instruction function at 55% becomes
  "these four arms are the wrong length". It is also how you catch a reorder that dropped a
  terminator: Ghidra's last arm carries no `break`, so moving it anywhere else makes it fall
  through - `arm_sizes.py` showed that arm 13 bytes *short*, and the listing showed the original
  ending it with `ret`.

- **A jcc pair differing only in the equality is an off-by-one in the condition.** `sweep_all.py`
  flags `-jg`/`+jge`, `-jl`/`+jle` and the unsigned equivalents over the same compare. Sometimes it
  is only an encoding (`cmp x, 0xa` / `jl` against `cmp x, 9` / `jle` mean the same thing - write
  the original's form), and sometimes the operands really do differ, so read the compare before
  acting. Check that the `cmp` itself is identical on both sides: if the original compares a
  register where we compare an immediate, the pairing is noise.

- **Instruction order inside a basic block is the scheduler's, not the source's.** The original
  reads `owner` before its `getValueOfTroopType` call in `recountTotalTroopValue`; moving our read
  to match cost *24 points*, because it forces a spill across the call where MSVC otherwise keeps
  the unit pointer and re-reads. Same for hoisting the layer pointers in `recomputeAttackInfo`.
  Reorder *blocks*, not instructions.

- **/GL does not rescue an allocator-bound function.** Adding the `pruneStale*` trio and the three
  find-slot scans to `cmake/compiler-flags-gl.txt` changed their codegen not at all - all six
  measured identical to the byte. Whatever decides the down-counter and the `mov [abs], esi` vs
  `eax` choice is not reachable through that flag either, so do not reach for per-file flags as a
  way out of register allocation.

- **A `(char)BVar1` that MSVC can fold is not a way to reuse a known-zero register.** The original's
  second `fillMemory_ByteValue` in `pruneStaleArcherPoints` passes the zero already in `eax`
  (`push eax`, one byte) where we emit `push 0` (two). Passing `(char)BVar1` instead of `'\0'` -
  provably the same value inside that branch - changes nothing, because MSVC const-folds it back.

### Ghidra's decompilation is the *starting point*, not the target

`giveLightPitchInstructionToUnitClosestToPitch` (0x51BF70) carries a
`decompilerscript: committed` banner - its Ghidra listing is the same text the
.cpp was seeded from. Three of its differences from our current file were tested
and all three lose:

| Ghidra's form | ours | delta |
|---|---|---|
| success block nested inside the `maxUnitCount` guard | early `if (!_minUnitID) return 0;` | -6.6 |
| `getPlayerNot1AndHasKeep(&DAT_TroopValueState, ...)` | `this` | -4.6 |
| both together | | -5.0 |

On a function already improved past its seed, Ghidra re-confirms the seed, not
the original. Check for the `decompilerscript: committed` banner first: when it
is there and our % is already well above where the seed would land, Ghidra has
no new information and the time is better spent on a function whose listing is
fresh.

### A local that only mirrors a global is really the *enregistered global*

The three slot scans (`findOrReserveArcherPointSlot`, `getSupportPointIndex`,
`getSiegeIndexForTile`) each had a `_firstFree` local written beside the
`...Next` global and never read for anything but its own zero-test. All three
sat at 76.6% on a single-instruction diff:

    - mov dword ptr [...Next], esi     <- original
    + mov dword ptr [...Next], eax     <- ours

`mov [abs32], eax` is the 5-byte `A3` form, `esi` needs 6 - and that one byte
shifted every jump displacement in the function, which is where the 23 points
went. MSVC had coalesced our `_firstFree = i; Next = _firstFree;` onto `eax`.

Deleting the local and testing/assigning the global directly took all three to
**100%** at once: with no call or aliasing store in the loop MSVC enregisters
the global in `esi` and writes through, which is exactly the original's shape.

Generalisation: when a local exists only to shadow a global, the original
probably had no local at all. Grep for a local assigned next to a global of the
same meaning and whose only other use is a predicate on itself.

### Cast the loop bound to `int` to stop MSVC strength-reducing a pointer walk

The `pruneStale*` trio all walked `point < &array[200]`, which MSVC turned into
a down-counter (`mov edi, 0xc7` / `sub edi,1` / `jne`) and an extra live
register; the original keeps the pointer compare (`cmp esi, <end>` / `jl`).
Writing the bound as

    } while ((int)point < (int)&...array[200]);

defeats the strength reduction and took all three from 70.7% to **77.1%**.

This is the first thing to try on any counted pointer loop whose diff shows a
`sub <reg>,1 / jne` where the original has `cmp <ptr>, <abs>`.

Not reachable (both tried and lost ~19 points each on this trio):
- walking an `int*` at the `tribeID` field offset, as Ghidra prints it, to kill
  the per-iteration `lea ecx,[esi-0x10]`. The lea is cheaper than whatever MSVC
  does to the field accesses afterwards.
- Ghidra's arm order here is the *inverted* one. The original lays the
  `!= someCounter1` (fill) arm first, which is what our file already had;
  taking Ghidra's `==`-first order costs the arm layout.

### Initialise a global *from* the local, not from a bare literal

`applyTribeBehaviorTypes` opened with

    int iVar2 = 0;
    int _index = 0;
    DAT_...unknownTribeCounterRelated = 0;

MSVC saw three independent zeros, coalesced two of the locals into one register
and stored the literal: `xor edx,edx` then `mov [global], edx`. The original
keeps two zeroed registers and stores `esi`. Rewriting the middle store as

    int iVar2 = 0;
    DAT_...unknownTribeCounterRelated = iVar2;
    int _index = 0;

took it 95.7% -> **100%**: reading `iVar2` forces MSVC to give it its own
register and store through it, and it fixes the `xor`/store order at the same
time.

Same family as [the spare local being the enregistered global]: whenever a
global and a local hold the same value, the *data flow between them* is what
pins the register allocation. Spell the dependency out - `global = local;` -
rather than writing the literal twice.

### Read the local, not the global, once you have cached it

`placeTunnelEntrances` did

    iVar2 = DAT_TileMapState::instance.placedBuildingID;
    if (0 < (int)DAT_TileMapState::instance.placedBuildingID) {
        ...buildings[DAT_TileMapState::instance.placedBuildingID].attackWave = ...;

The original tests the cached value and indexes with a *copy* of it, giving
`mov eax,[global] / test eax,eax / mov ecx,eax / imul ecx,0x32c`; our re-reads
made MSVC pick the opposite registers, which also flipped two `push` operands.
Replacing both re-reads with `iVar2` took it 88.6% -> **100%**.

This and the two entries above are one rule in three costumes: **the original's
register allocation is a shadow of the source's data flow, so write the data
flow the registers imply.**

- global written beside a local that mirrors it -> drop the local, use the global
  (the three slot scans, 76.6% -> 100%)
- global initialised to a literal a local also holds -> `global = local;`
  (`applyTribeBehaviorTypes`, 95.7% -> 100%)
- global cached in a local and then re-read -> read the local
  (`placeTunnelEntrances`, 88.6% -> 100%)

Each is worth a mechanical grep across the namespace. Three of the four known
100% jumps this session came from this family.

Scheduler-bound, do not retry: `initializeAttackZoneSearch` (77.8%) and
`findEnemyLord` (78.0%) differ only in load placement inside one basic block and
in which register holds the count vs the walk pointer.

#### ...but the direction is per site, so measure

Replacing the re-read with the cached local was swept over six functions in one
build (scores are per-function, so one build evaluates them all):

| function | before | after |
|---|---|---|
| `trySendKnightTribeToAttack` | 62.1 | **100.0** |
| `collectArcherUnitsByLocation` | 75.9 | 63.7 |
| `commandUnitsToMoveToKeep` | 77.6 | 73.7 |
| `executeAttackWaveTargetAssignment` | 88.5 | 82.4 |
| `recountAttackTroopValue` | 75.9 | 65.9 |

One big win, four clear losses. The rule says *the register allocation implies a
data flow*, not *caching is always right* - sometimes the original really does
re-read. Sweep the candidates, keep the winners, and do it in a single build.

### sweep_all.py CONST and SIGNED hits drift out of alignment - verify before trusting

A full sweep after this session's structural wins produced four plausible-looking
constant mismatches. All four were artefacts of the aligner pairing the original's
*next* comparison against ours, and all four lost points when "fixed":

| reported | reality |
|---|---|
| `computeAttackWaveTroopComposition` orig 0x4 vs ours 0x2 | ours cmp 2 paired with orig's cmp 4 from the *following* `5 <= x` test; `4 < x` -> 66.8 to 65.9 |
| `executeAttackWaveTargetAssignment` orig 0x3 vs ours 0x6 | same drift one test over; `< 3`/`< 7`/`< 13` -> 88.5 to 88.3 |
| `setRallyPointForLaddermenTribe` SIGNED jl/jb | int-casting the bound is exactly neutral here |
| `assignMacemen...` orig 0x12 vs ours 0x13 | `cmp 0x12/jle` and `cmp 0x13/jl` are the same test; MSVC canonicalises `<= 18` back to `< 19`, exactly neutral |

Before acting on a CONST hit, read both sides' surrounding comparisons and check
the hit is not just our test aligned against the original's neighbour. A CONST
hit is only real if the two tests it pairs are the *same* test.

Also measured and reverted (the cached-local substitution, wrong direction here):
`scanForArcherPoints` 82.7 -> 77.7, `scanForSiegeTentPoints` 41.7 -> 34.5.

### A boolean argument that the original *branches* on wants two call sites

`aiRecomputeAttacks2` passed `(int)(BVar3 != 0)` to `computeAIZoneLayer`, which
MSVC renders branchlessly as `xor eax,eax / setne al`. The original branches:
`je / push 1 / jmp`. Writing the call twice under an `if (BVar3) ... else ...`
with literal `1` and `0` gives the branch and took it 87.6% -> **89.2%**.

`BVar3 ? 1 : 0` is *not* a substitute - it compiles bit-identically to
`(BVar3 != 0)` (measured, 87.6%). MSVC only branches when the two argument
values reach the call from genuinely different paths, so the call has to be
duplicated.

Note this cuts the opposite way from `computeAttackWaveTroopComposition`, where
reading `setne` in the original's listing and converting two assignments to
`(x != 0)` form collapsed it from 66.8% to **13.7%** - that `setne` belonged to a
different statement that the aligner had drifted onto. Confirm which statement a
`setne` belongs to before acting on it.

### Rebase parameter arithmetic onto the derived local that already holds it

`renderAttackInfoDebugOverlay` computed `xParam = x + 2` once and then wrote
`x + 0x16` (4 sites) and `x + 0x20` (2 sites) for later columns. The original
emits `lea eax,[esi + 0x14]` from the register already holding `xParam`, while
ours re-read the parameter off the frame and added the absolute offset - which
also cost an extra dword of frame (`sub esp,0x3f0` vs `0x3ec`).

`x + 0x16` is `xParam + 0x14`, same value. Rewriting all six sites relative to
`xParam` took it 82.4% -> **95.8%**, and the rest of the gap is only reccmp
mis-symbolising the literal `0xffffff` (white) as `BuildingsState+424671` plus
the security-cookie names.

Fourth instance of the data-flow rule. Worth grepping for: two expressions on
the same parameter with different constants, where one of them is already a
named local - the later ones are probably offsets from that local, not from the
parameter.

#### Sweep result, round two (same substitution, five more functions)

| function | before | after | kept |
|---|---|---|---|
| `updateTribeBehaviorBasedOnBehaviorType` | 55.0 | **71.3** | yes |
| `sortAttackInfoTribeIDArrayBasedOn` | 74.5 | **83.1** | yes |
| `placeSiegeTentOrTunnelAtSuitableLocation...` | 83.2 | **84.2** | yes |
| `placeTunnelForEveryTunneler` | 70.2 | 56.0 | no |
| `placeSiegeTentsAndAssignEngineers` | 32.6 | 28.1 | no |
| `ifNecessaryThrowOilAutomatically` | 36.5 | 35.9 | no |

Running tally for "read the cached local, not the global": **5 wins (two of them
to 100%), 8 losses.** It is the single highest-yield substitution found so far
and it is still only slightly better than a coin flip per site, so it must be
swept and measured, never reasoned about. Batch every candidate into one build -
scores are per-function - then revert the losers.

The scan that finds the candidates:

    local = <DAT_...global expr>;   ...and that same expr appears again later

### `x + -1` and `x - 1` are the same instruction - do not chase it

`updateTribeBehaviorBasedOnBehaviorType`'s diff shows the original using
`sub eax,1` where ours emits `add eax,-1`, which looks like the Ghidra `+ -1`
idiom leaking into codegen. It is not. Rewriting every `+ -1` as `- 1` across
all twelve sub-100 files that contain it changed **nothing**: all twelve scored
bit-identically. MSVC canonicalises the two forms.

Keep `+ -1` - it is what the already-100% files in this directory use.

### Do not reorder the three top-level arms of `updateTribeBehaviorBasedOnBehaviorType`

Its dispatch is `cmp eax,0x3f2` followed in the original by `jg <high> / je <eq>`
where ours emits a single `jge`, which reads as though the original ordered the
arms high-switch / `== 1010` / low-switch while ours has low / `== 1010` / high.
Rewriting the chain into that order (same bodies, conditions negated) collapsed
it **71.3% -> 21.3%**.

The two switches are ~76 and ~308 lines; moving either past the other relocates
every jump-table entry and every arm, so the per-arm layout that previous
sessions tuned (see the corrected arm order above) is worth far more than the
dispatch's two-instruction shape. Treat the dispatch `jge`/`jg`+`je` difference
as a 2-instruction cost and leave the arms where they are.

## Prioritise by starting percentage: local fixes only pay above ~70%

Tally of every change measured in this session, by the function's starting score:

**Starting >= 70% - 13 wins, 0 regressions kept:**
slot scans +23.4 (x3, to 100%), `renderAttackInfoDebugOverlay` +13.4,
`trySendKnightTribeToAttack` +37.9 (to 100%), `placeTunnelEntrances` +11.4
(to 100%), `applyTribeBehaviorTypes` +4.3 (to 100%), `sortAttackInfo` +8.6,
`pruneStale*` +6.4 (x3), `aiRecomputeAttacks2` +1.6,
`placeSiegeTentOrTunnel...` +1.0.

**Starting < 70% - one win (+16.3), everything else lost:**
`ifNecessaryThrowOilAutomatically` (36.5): cached local -0.6, `< 1`->`<= 0` -6.2,
and -6.3 for that same edit *in isolation at the exact site the diff flagged*.
`placeSiegeTentsAndAssignEngineers` (32.6): cached local -4.5, `<= 0` -4.1.
`computeAttackWaveTroopComposition` (66.8): `setne` -53.1, CONST -0.9.
`recomputeAttackInfo` (30.5): int-cast bound +0.1.

**Why:** reccmp aligns instruction streams. Below roughly 50-70% the two streams
are already badly out of phase, so a *correct* one-instruction fix re-phases the
alignment somewhere else and the score drops. The `<= 0` edit above is almost
certainly right - the original really does emit `test edi,edi / jg` - and it
still measured -6.3.

**Consequences:**
1. On a sub-70% function the score cannot validate a local fix. Do not grind
   single-site edits there and do not trust a regression as evidence the edit was
   wrong.
2. Sub-70% functions need a change large enough to re-phase the whole function -
   arm order, a dropped `return`, a restructured loop - the kind of thing found
   by reading Ghidra's control flow, not by reading a diff.
3. Spend diff-reading time on the 70-99% band. That is where every win came from.

## The induction-pointer anchor is not source-controllable - stop trying

Four functions differ almost entirely in *which struct field* MSVC anchors the
loop's induction pointer on, which shifts every field offset and the loop bound
in the diff and costs roughly 20 points each:

| function | % | original anchor | ours |
|---|---|---|---|
| `exitSiegeEquipmentForWave` | 77.7 | `TribesState+886` | `+1520` |
| `recountAttackTroopValue` | 75.9 | `TribesState+886` | `+864` |
| `commandUnitsToMoveToKeep` | 77.6 | `UnitsState+2866` | `+2874` |
| `sortAttackInfoTribeIDArrayBasedOn` | 83.1 | `TribesState+1025064` | anchor-0x18 |

The decisive evidence is `recountAttackTroopValue`: both sides access exactly
the same three fields (884, 864, 912), so MSVC had a free choice of base and
simply picked differently. The anchor is chosen downstream of register pressure
and instruction order, not from anything spellable in the source.

Tried and failed:
- hoisting the read of the field the original anchors on, so it is the first
  access (`exitSiegeEquipmentForWave`, exactly neutral - MSVC sinks the load back
  into the branch)
- walking an explicit `int*`/`short*` at the original's offset (`pruneStale*`,
  -19 points; also -12 on a second shape)
- writing the loop bound symbolically instead of as a literal
  (`sortAttackInfo`, -2.5 raw, twice)

Treat these four as regalloc-bound. Their remaining ~20 points each are not
reachable from C++.

Also neutral, do not retry: moving `placeTunnelForEveryTunneler`'s zero
initialisations after the `if (!local_c)` test to stop MSVC reusing a zeroed
register as the comparison operand. MSVC reorders them back.
