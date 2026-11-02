# The `/GL` conundrum, solved: what the original's source layout was, and how we reproduce it

*Branch `docs/msvc-stack-slot-order`, 2026-11-02. Everything below was measured with the bundled MSVC 14.00.50727.762
toolchain against `Stronghold Crusader.exe` 1.41; the commands to repeat each measurement are given inline.*

## TL;DR

- The pattern we have been calling "LTCG" - the original keeps `ecx`/`edx` live across a call where our build
  spills `this` into `esi` - has nothing to do with `/GL`. The original was built with **no `/GL` object at all**.
- The compiler backend (`c2.dll`) remembers which registers every function it has already compiled writes, and
  when it later lowers a call to that function **in the same translation unit** it kills only those registers.
  That is the whole effect.
- Hence the layout question has a definite answer: the original compiled **several classes per `.cpp` file as
  ordinary translation units**. Not one function per file. Not method bodies in headers. Not `/GL`.
- Inside a unit the compiler emits callees before callers regardless of source order, so **source order does not
  matter**, and that bottom-up emission leaves a fingerprint in the image that lets us read the unit boundaries
  off the function addresses.
- For the project the practical rule is unchanged: keep one function per file, put caller and callee in
  `cmake/compiler-flags-gl.txt`, and switch the callee's function resolver on. New: `tu_merge.py` tells you in
  twenty seconds whether a given callee belongs on that list, before you touch the list.

## 1. The original has no `/GL` objects

`tools/compiler-internals/rich_header.py FILE` decodes a PE's Rich header, the per-object record of which tool
built it. Calibrated against the bundled toolchain (we compiled probes and read their headers back):

| product id | tool |
|---|---|
| 0x6d / 0x6e | `cl` C / C++, no `/GL` |
| 0x71 / 0x72 | `cl` C / C++ with `/GL` |
| 0x7d | `ml.exe` (MASM 8.00) |
| 0x78 | `link` 8.00 |

The original: 170 C objects, 100 C++ objects, 38 assembler objects, **zero `/GL` objects**. The 38 assembler
objects are the static CRT. (An earlier table in our docs read 0x7d as "LTCG C++"; that was wrong and has been
corrected everywhere.)

```
python tools/compiler-internals/rich_header.py "_original/Stronghold Crusader.exe"
```

## 2. What the compiler actually does

Two routines in `c2.dll`, now documented as plate comments in the `c2.dll` Ghidra project:

- `MscCollectUsedRegs` (0x10ba2030) runs after register allocation of a function and collects the set of
  registers the function writes (every register destination of every real instruction, register sets OR'ed,
  recursive self-calls skipped). The result is stored on the function's own record.
- `LoAddCallScratchRegs` (0x10c3f5f0) runs when lowering a `call`. If the callee symbol is a function **defined in
  this module** and has a function record with that register set filled in, only the *volatile* registers in that
  set are marked clobbered. Otherwise all volatile registers (`eax`, `ecx`, `edx`) are killed.

So when the callee never writes `ecx`, a caller compiled afterwards in the same unit may keep `this` in `ecx`
across the call. A caller in another unit does not know that and spills. `/GL` reproduces the effect across files
because link-time code generation makes the whole program one module, which is why the `/GL` list worked, but it is
a workaround for a layout difference, not evidence that the original used it.

Three consequences, each tested below:

1. the callee must be compiled in the same translation unit as the caller;
2. source order inside the unit is irrelevant, because `c2` emits a unit bottom-up (callees before callers);
3. an `inline` body in a header does not count, even when the compiler decides not to inline it.

## 3. The test scenarios

Tool: `tools/compiler-internals/tu_merge.py CALLER.cpp CALLEE.cpp [...]`. It writes three scratch translation
units under `build-RelWithDebInfo/batch/variants/tu_<caller>/` and diffs the caller in each against the original
with `quick_diff.py --name CALLER` (one `/FA` compile, no link, no `/GL`, about six seconds each):

| layout | file |
|---|---|
| callee in another unit (the committed state) | `caller_only.cpp` |
| callee pasted into the caller's file *before* the caller | `callees_first.cpp` |
| callee pasted *after* the caller | `caller_first.cpp` |

All function resolvers were on for every measurement (the compiler never sees our callee otherwise).

### 3a. One pair in detail: `updateMoatCountdownTimers` -> `recountTotalOwnedMoats`

| scenario | match |
|---|---|
| separate files | 0.5128 |
| same file, callee first | **1.0000** |
| same file, callee after the caller | **1.0000** |
| callee as an `inline` body in a header, not inlined | 0.5128 |

Same file in either order: byte-identical to the original. Header body: no effect. `copyData` with its three
callees (`encodeData`, `decodeData`, `swapMapDataWithNextMap`, three different classes) behaves identically:
0.4615 alone, 1.0000 merged either way.

### 3b. Does source order matter? (`order_probe.py`)

`tools/compiler-internals/order_probe.py` generates a unit with three classes at call depths 0, 1, 2 written
**top-first** in the source, compiles it with `/O2`, `/O2 /Ob0` and `/Od`, and reads the function order out of the
`/FA` listings:

- `/O2` and `/O2 /Ob0`: leaves first, then the middle level, then the tops. Source order is discarded.
- `/Od`: source order.

It then links the objects and shows the image keeps objects contiguous in command-line order. Together: inside an
optimised unit every callee sits at a **lower address** than its caller, and units follow each other in the order
the files were given to the linker.

### 3c. The whole `/GL` list (`tu_merge.py --batch`)

Every file of `cmake/compiler-flags-gl.txt` against each of its resolvable callees, one at a time, then all
callees that sit below the caller together. Pairs that moved:

| caller | callee pasted in | alone | merged |
|---|---|---|---|
| `processSyncPacket` | `translateMultiplayerIDsIntoPlayerIDs` | 0.2667 | **1.0000** |
| `updateMoatCountdownTimers` | `recountTotalOwnedMoats` | 0.5128 | **1.0000** |
| `updateNeededEmployeeCount` | `hasWorker` | 0.5965 | **1.0000** |
| `buildingIsAccessible` | `getBuildingHeightForBuildingID` | 0.6079 | **1.0000** |
| `canUnitReachBuildingPerimeter` | `getBuildingHeightForBuildingID` | 0.7731 | **1.0000** |
| `encodeData` / `decodeData` / `swapMapDataWithNextMap` | `copyData` | 0.98 / 0.99 / 0.99 | **1.0000** |
| `readFirst/NextPartOfCurrentResourceIntoMemory` | `putFileNameAndAppendFileExtension` | 0.98 / 0.98 | **1.0000** |
| `UpdateArmorersWorkshop` .. `UpdateBakery` (5 functions) | `updateVisuallyActiveState` | 0.35-0.43 | **0.9945-0.9979** |
| `UpdateStables` | `validateBuildingTetheredUnits` | 0.6642 | **1.0000** |
| the same `Update*` callers | `playSFXAtLocation` | 0.35-0.44 | 0.57-0.82 |
| `destroyBuildingAndLinkedDuplicates` | `destroySignpostData` | 0.6875 | 0.9375 |
| `lightUpBuilding` | `getBuildingFlammabilityFactor` | 0.8988 | 0.9268 |

Three pairs got **worse** when merged: `addBuildingToTargetableBuildings` into every `Update*` function,
`selectionContainsOnlyArabAssassins` into `canUnitReachBuildingPerimeter`, `getFireEntityIDAtTile` into
`lightUpBuilding`. That is the converse proof: once the compiler knows that callee's registers it allocates the
caller differently (an extra stack slot, `ebx`/`ebp` swapped), and the original did *not* know, so that callee
lived in another file. Inlining is not the cause; call counts are unchanged. 53 pairs did not move at all, so
those callers' remaining differences are about something else.

Note the `Update*` workshop functions are free functions in `OpenSHC::Map::Buildings` while
`updateVisuallyActiveState` is a `BuildingsState` method, and `copyData` (`LowLevelMemory`) shares a unit with
`DecoderState` and `ResourceManager` methods: **the original's files held several classes each**.

## 4. Reading the original's file layout off the image

`tools/compiler-internals/tu_layout.py` parses every `*.func.hpp` resolver (address, class, name) and every
`MACRO_CALL` in our sources, and applies the rule from 3b: inside one unit the callee is always below the caller,
so a call that goes **upward** in the address space crosses a unit boundary.

```
python tools/compiler-internals/tu_layout.py calls     # statistics over all resolved call pairs
python tools/compiler-internals/tu_layout.py units     # minimum set of unit boundaries, with class composition
python tools/compiler-internals/tu_layout.py pairs     # the /GL list: is each callee below its caller?
python tools/compiler-internals/tu_layout.py around NAME
```

Over all 1349 resolved call pairs, 952 (71%) point downward. Within 64 KB, 595 point down and 36 up: the upward
ones are the cross-file calls. Interval stabbing of the upward calls needs at least 10 boundaries, i.e. **at
least 11 units**, and the segments between them are large and mixed:

| address range | functions | classes (largest) |
|---|---|---|
| 0x401000-0x449d50 | 695 | BuildingsState, Map::Buildings, UI::BuildingMenus, EntityState, Map::Entities |
| 0x449dc0-0x4572a0 | 114 | TextureRenderCore, SFXState, GameStateStructures |
| 0x4574c0-0x4680b0 | 225 | GameStateStructures, TextEditorState, BuildingAndStatusMenu |
| 0x4680c0-0x479a60 | 242 | ResourceManager, PencilRenderCore, UserTextHandler, TextManager, GameCore, LowLevelMemory |
| 0x479ab0-0x47b3c0 | 34 | SoundSystem |
| 0x47b490-0x4a9eb0 | 428 | PathFindingState, Synchrony::Commands, GameSynchronyState |
| 0x4a9ed0-0x4b7af0 | 148 | DisplayElements, MinimapViewState, MenuModalComposition |
| 0x4b7c90-0x4edc90 | 452 | AICState, ViewportRenderState, MapPropertiesState, UI::Credits |
| 0x4edcb0-0x4f9930 | 140 | TileMapState, LandscapeState, AIVState, Rocks, Trees |
| 0x4f9980-0x5369f0 | 543 | TileMapState, UnitsState, TribesState, TroopValueState |
| 0x536a60-0x59d7f2 | 642 | Global::Init, Meta, Map::Units, UnitsState |

Read these as upper bounds on file extent: the stabbing gives the *fewest* boundaries that explain the upward
calls, so the real files may be smaller, and the list grows as more functions are reimplemented and more calls
resolve. What is not in doubt is the shape: the same class sequence repeats three or four times inside one
segment (around 0x466000-0x475000 for example), which is what several call-depth levels of one bottom-up unit look
like, not what several files look like.

Also note that "callee below caller" is a necessary condition for same-unit, not a sufficient one:
`getFireEntityIDAtTile` sits below `lightUpBuilding` and still measures as another unit.

## 5. Answers to the questions asked

**Were multiple `.cpp` files merged?** The original was compiled from a modest number of large source files,
each holding several classes. Whether a given pair sat in one file is now a measurement (`tu_merge.py`), and the
merged-is-worse cases show the original did not have everything in one place either.

**Were all method bodies declared in `.hpp` files?** No. A header body (with `inline`) does not give the compiler a
register record for the callee, so it cannot produce the pattern. Only an out-of-line definition in the same unit
does.

**Does `/GL` matter?** Not for the original. For us it stays the practical fix while the project keeps one function
per file, because it makes the compiler treat caller and callee as one module and is the only layout-neutral way to
get the register record across files.

## 6. What to do when you hit the pattern

You see it as: the original keeps `ecx` or `edx` live across a call where ours reloads or spills `this`, and every
register downstream of that call is renamed.

1. Make sure the callee is finished and its `MACRO_FUNCTION_RESOLVER` flag is on. With it off the compiler calls
   the original binary and can never know the callee's registers; `processSyncPacket` read 26% for that reason
   alone.
2. Run `python tools/compiler-internals/tu_merge.py CALLER.cpp CALLEE.cpp`. If `callees_first` beats
   `caller_only`, add both files to `cmake/compiler-flags-gl.txt`. If it is worse, do not: the original did not
   have that callee in its unit, and adding it will cost you.
3. A caller with several unit-mates may only move once *all* of them are known; `tu_merge.py --batch` prints an
   `ALL n callees below` row for that case, and `tu_layout.py around NAME` lists the candidates.
4. Confirm with a full build and reccmp, as always.

## 7. Tools added or changed on this branch

| tool | purpose |
|---|---|
| `tools/compiler-internals/tu_merge.py` | the three layouts of a caller/callee pair; `--batch` over the `/GL` list |
| `tools/compiler-internals/tu_layout.py` | `runs`, `units`, `pairs`, `calls`, `around`: the layout read off the image |
| `tools/compiler-internals/order_probe.py` | proves bottom-up emission and link order on a synthetic unit |
| `tools/compiler-internals/rich_header.py` | which tools built a PE's objects; no `/GL` in the original |
| `tools/reimplementation-helper/batch/quick_diff.py --name NAME` | pick one function out of a multi-function file |

`quick_diff.py` also had three normalisation gaps fixed on the way (struct offsets above 0x400000, `ret 0`
versus `ret`, switch byte and jump tables); `lightUpBuilding` reads 0.9312 instead of 0.8988 on the same code
because of that alone, so compare old `quick_diff` numbers with care.

Docs updated to the same story: `tools/compiler-internals/msvc-backend.md` (section "The /GL conundrum", with the
full batch table), `tools/compiler-internals/finding-mismatches.md` (step 0), `AGENTS.md` and
`IMPLEMENTATION_CHEAT_SHEET.md` (the former "LTCG" bullets).

## 8. Caveats and open ends

- Nothing on this branch is committed yet, and the working tree has every function and struct resolver flipped on
  (never to be committed).
- `UpdateInn.cpp` does not compile on this branch (missing `padding_0x2b2`), so it is absent from the batch.
- The `Update*` workshop functions stop at 0.995-0.998 with one unit-mate and need `playSFXAtLocation` as well;
  that pair was measured per-callee only. Worth a run with both.
- The unit map in section 4 is a lower bound on the number of files. If someone wants the real boundaries, more
  reimplemented callers in the sparse regions (0x4a9ed0-0x4b7af0, the UI code) would tighten it fastest.
