# Reimplementation Style Guide

This guide describes how a reimplemented `.cpp` should read in terms of style. [AGENTS.md](AGENTS.md) covers the workflow and
[IMPLEMENTATION_CHEAT_SHEET.md](IMPLEMENTATION_CHEAT_SHEET.md) how to improve match results. This file is about the source file that is created.

Rules marked **neutral** cost nothing. Rules marked **measure** have been seen to
change code generation sometimes, so always check if match results drop after applying the style.
Usually, following this style improves the match results.

The overriding rule: **the match comes first.** A readability change that costs a percent is not a
readability change, it is a regression in matching. When a rule and the match disagree, keep the ugly form and leave a
comment saying what was measured, so the next reader does not retry it.

---

## 1. Drop the decompiler's trailing `return;`

Functions that return `void` don't need an explicit `return;` at the end of the function body.

```cpp
// no
void GameStateStructures::activateTraderState()
{
    this->mapAndTime.traderRelated2 = 2;
    this->mapAndTime.traderRelatedCounter1 = 0;
    return;
}

// yes
void GameStateStructures::activateTraderState()
{
    this->mapAndTime.traderRelated2 = 2;
    this->mapAndTime.traderRelatedCounter1 = 0;
}
```

**neutral.** Only the *trailing* one goes. An early `return;` inside an `if`, a loop or a `switch` arm is
control flow and must stay obviously. 

> Note: A regex over `return;\n}` will eat early returns in nested blocks, because their closing
brace looks the same; match on the function's own closing brace (`    }` at four spaces against a statement
at eight) or do it by hand.

## 2. No cast on a `BOOLEnum` return

`BOOLEnum` is `typedef BOOL`, which is `int`, so a comparison converts to it implicitly and yields exactly
0 or 1. The decompiler's `(uint)` says nothing generally speaking, but there are exceptions.

```cpp
// no
return (uint)(this->mapAndTime.playerTeams[a] != this->mapAndTime.playerTeams[b]);

// yes
return this->mapAndTime.playerTeams[a] != this->mapAndTime.playerTeams[b];
```

Generally **neutral**.

## 3. No cast that only repeats the destination type

```cpp
short first500BuildingsPerPlayer[9][500];

// no
this->first500BuildingsPerPlayer[owner][idx] = (short)buildingID;

// yes
this->first500BuildingsPerPlayer[owner][idx] = buildingID;
```

**neutral**, and silent at `/W3` — the narrowing is already implied by the field, so the cast buys neither
code nor a warning. Check both: a cast that silences a real `/W3` warning earns its place, and a cast in a
*condition* or an *argument* is not covered by this rule, because there the conversion is the operation.

## 4. `sizeof` instead of a byte count — but only when it is provably the same

```cpp
// no
fillMemory_ByteValue(14836, '\0', &this->playerDataArray[playerID]);

// yes
fillMemory_ByteValue(sizeof(this->playerDataArray[playerID]), '\0', &this->playerDataArray[playerID]);
```

**neutral**, and it ties the call to the layout, so a header correction can no longer leave the clear behind.

**Verify the arithmetic before every single substitution.** Over seven `fillMemory_ByteValue` calls in
`GameStateStructures`, only three of the constants actually equalled the field:

| call | constant | `sizeof` | |
|---|---|---|---|
| `playerDataArray[playerID]` | 14836 | 14836 | substituted |
| `mapAndTime` | 262608 | 262608 | substituted |
| `unitMoveDestinationXYPairs` | 0xa00 / 2560 | 2560 | substituted |
| `signpostIDs` | 0x40 | 32 | **left alone** |
| `signpostEntryData` | 0x100 / 256 | 128 | **left alone** |
| `signpostsMapEdge` | 0x1900 / 6400 | 5600 | **left alone** |

The four that disagree are not rounding: the original clears more bytes than the generated header declares,
and `clearDataAndSignpostDataIfNecessary` already carries `fixme` comments about it. Substituting `sizeof`
there would silently shrink a memset and change behaviour, which no percentage would catch — the call target
is the same. Leave the constant, keep the `fixme`, and fix the header instead.

## 5. Flags that only hold 0 or 1 are `BOOLEnum`, and are tested as such

```cpp
// no
int isAI = 0;
...
isAI = 1;
...
if (isAI != 0) {

// yes
BOOLEnum isAI = FALSE;
...
isAI = TRUE;
...
if (isAI) {
```

**neutral** — `BOOLEnum` is `int`, so nothing moves.

Prove the claim before making it. The test is *every* store, not the name:

- a **local** whose stores are all `0`/`1` is provable by reading the function — `isAI` in
  `checkRequiredResourcesForBuildingOrPlanToBuy` and `signpostMoved` in
  `clearDataAndSignpostDataIfNecessary` are the two in this namespace.
- a **field** usually is not. Most are written by original code we have not reimplemented, so our source
  cannot show the range. `currentAIArray[playerID] != 0` reads like a boolean and is not one: it holds the
  AI lord's identity, and the comparison asks whether the slot is taken. Leaving `!= 0` is the honest form.
- a **counter** keeps its comparison. `livingPlayers != 0` and `allowedCount >= 2` are quantities;
  `if (livingPlayers)` would read as a flag test.

So `!= 0` is not a wart to be removed on sight. It is the right spelling for *is this non-zero*, and only
the wrong one for *is this true*.

## 6. `const` on a local that is assigned once

Written **after** the type, matching the project's existing `int const*` spellings:

```cpp
// no
int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;

// yes
int const owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
```

**measure.** It is neutral in every case measured here, but `const` is exactly the kind of extra information
that lets MSVC rematerialise a value instead of spilling it, and a changed spill changes every stack
displacement after it. Re-run `reccmp_report.py cmp` over the files touched.

A local does not qualify if anything later assigns it, steps it (`++`, `--`, `+=`), or takes its address.
Loop counters never qualify. A `const` that has to be removed again later to accommodate a fix is worse than
no `const`, so prefer it on reads of state that the function plainly only samples once.

## 7. Resolve a pointer into a field or an array access

Ghidra turns field walks into pointer arithmetic, and the offsets it leaves behind can point into a
completely different member. `unptr.py` and `unoffset_matrix.py` undo the common shapes.

```cpp
// no — [0x1b] is not this array at all, it is currentAIArray[playerID]
int* currentPlayerFullID = &...currentPlayerFullIDArray[playerID];
if (*currentPlayerFullID == -1 && currentPlayerFullID[0x1b] == 0) {
```

**measure, and expect this one to fight back.** Naming both arrays is the readable form:

```cpp
if (...currentPlayerFullIDArray[playerID] == -1 && ...currentAIArray[playerID] == 0) {
```

and in `createStatsPopUpEntities` it costs the match. MSVC keeps one induction register either way, but
naming the second array moves the anchor onto it: the two reads become `[edi - 0x6c]` and `[edi]` where the
original has `[edi]` and `[edi + 0x6c]`. Same 38 instructions, two of them different — `quick_diff` 0.9737
down to 0.9211. The cheat sheet records the general pattern (*two arrays of one struct in a condition*).

When the pointer has to stay, pay for it in comments rather than leaving a bare magic offset: say which
member the offset reaches, show the arithmetic from the header (`0x714 - 0x6a8 = 0x6c`), and record the
measurement so nobody retries it. Make it `int const* const` while you are there.

## 8. Let the compiler unroll

A body repeated four times with `playerID`, `playerID + 1`, `playerID + 2`, `playerID + 3` is not something
a human wrote. The original's compiler unrolled an ordinary loop, and ours does too.

```cpp
// no — 49 lines, four copies, outer loop stepping by 4
for (int playerID = 1; playerID < 9; playerID += 4) {
    if (...[playerID] ...) { ... }
    if (...[playerID + 1] ...) { ... }
    if (...[playerID + 2] ...) { ... }
    if (...[playerID + 3] ...) { ... }
}

// yes — 12 lines, byte-identical output
for (int playerID = 1; playerID < 9; ++playerID) {
    if (...[playerID] ...) { ... }
}
```

**neutral** on `areActivePlayersMostlySameTeam`: 73 instructions against 73, and the only line `quick_diff`
reports is its own `ret`/`ret 0x0` formatting artefact. Try the plain loop before writing copies out, and if
a hand-unrolled body is already in the tree, try collapsing it.

## 9. Declaration order outranks loop shape

A `while` that a `for` would say better can usually become one — but the conversion must not reorder the
declarations, because MSVC assigns stack slots and registers in declaration order (see `perm_decls.py`).

```cpp
// no — allowedCount is now declared before index, and the two xor instructions swap
int allowedCount = 0;
for (int index = 0; ...[index] != -1; ++index) {

// yes — same order as before, still a for loop
int index = 0;
int allowedCount = 0;
for (; ...[index] != -1; ++index) {
```

On `anyGoodsAreAllowedForSale` the first form moves `xor esi, esi` one instruction earlier and takes
`quick_diff` from 0.9048 to 0.8571; the second is byte-for-byte the `while` loop it replaced. Hoisting the
initialiser out of the `for` header looks like a half-done conversion, so say why in a comment or leave the
`while` alone.

## 10. No magic addresses

For example, sometimes addresses are referred in while loops, but in reality, they are not used: looping over the array
with a for-loop naturally reproduces the address in the machine code without the literal address being required in the source code.
```cpp
ptr = &value;
while (ptr < 0x401000) {
    ptr += 4;
}
```

## 11. Prefer for-loops everywhere
All do-while and while loops should be rewritten as for-loops.

## 12. Literal strings should be imported
Literal strings should be replaced with the appropriate entry from:
src/OpenSHC/string-literals.hpp or src/OpenSHC/wstring-literals.hpp

## 13. One function per file, and the file is named after it

Almost every `.cpp` on `main` holds exactly one function (1078 of 1087), and the file name is the function
name.

```text
src/OpenSHC/Game/GameStateStructures/activateTraderState.cpp   -> activateTraderState()
src/OpenSHC/IO/ResourceManager/getCurrentResourceCoreNameUnk.cpp -> getCurrentResourceCoreNameUnk()
```

The folder is the class: a method of `ResourceManager` lives in a folder called `ResourceManager`.

If you add a second function to a file, the next person cannot find it by name. Make a new file.

## 14. The shape of a file

Every file looks like this. Copy it.

```cpp
#include "../ResourceManager.func.hpp"          // 1. your own class, with ../

#include "OpenSHC/Globals/DAT_CurrentResourceCoreName.hpp"  // 2. everything else, after a blank line

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471D30
    char* ResourceManager::getCurrentResourceCoreNameUnk()
    {
        ...
    }

} // namespace IO
} // namespace OpenSHC
```

Three things to copy exactly:

- the first include is your own class, written with `../` (773 files do it this way).
- the `// FUNCTION:` line sits directly above the function. **Never change the address in it.**
- the body is indented one step per `namespace`.

## 15. Write `- 1`, not `+ -1`

The decompiler writes "plus minus one". People write "minus one". It is the same number.

```cpp
// no
if (this->cursorPosX >= ...screenHorizontalResolutionInPixels + -1) {
for (int basenameStart = basenameEnd + -1; basenameStart >= 0; --basenameStart) {

// yes
if (this->cursorPosX >= ...screenHorizontalResolutionInPixels - 1) {
for (int basenameStart = basenameEnd - 1; basenameStart >= 0; --basenameStart) {
```

**neutral.** The compiler sees one value either way. There are still 15 of these on `main`.

## 16. Give variables a name that says what they hold

The decompiler invents names like `iVar5`, `uVar2`, `local_8`, `bVar1`. These names mean nothing. A reader
cannot guess what the value is, and cannot see when it is wrong.

```cpp
// no
int iVar5 = ...field21_0x70 - 34;
if (iVar5 < 0 || 7 < iVar5) {
    iVar5 = 0;
}

// yes
int musicSetIndex = ...field21_0x70 - 34;
if (musicSetIndex < 0 || 7 < musicSetIndex) {
    musicSetIndex = 0;
}
```

**neutral.** A name is not code.

You do not have to be sure what the value is. `musicSetIndexUnk` is still better than `iVar5`, and the
project already uses the `Unk` ending for "we do not know yet".

## 17. `i` is fine for counting, a name is better for meaning

```cpp
// counting characters: i is enough
for (int i = basenameStart; i < basenameEnd; ++i) {
    DAT_CurrentResourceCoreName::instance[i - basenameStart] = _resourceName[i];
}

// the value means a player: give it a name
for (int j = 0; j < candidateCount; j++) {
    int const targetPlayer = candidates[j];
    if (...currentPlayerFullIDArray[targetPlayer] != -1) {
```

**neutral.** Do not rename a loop counter into something long. Name the thing you *read out of* the array.

## 18. Use the name, not the number

The project already has names for most numbers. Search before you write a number.

```cpp
// no
...[playerID][15] = 500;
this->streamFlagsUnkAndLoopCount_0x34[3] &= ~0x80000000;
drawText(..., 0x7fff);   // some raw colour value

// yes
...[playerID][Game::Resources::RT_GOLD] = 500;
this->streamFlagsUnkAndLoopCount_0x34[3] &= ~FLAG_SOUND_UNINTERRUPTABLE;
drawText(..., COL_WHITE::instance.shortValue);
```

**neutral** — the name *is* the number. Where to look:

| kind of number | look for |
|---|---|
| resource (gold, meat, ...) | `RT_...` |
| building | `BT_...` |
| unit | `UT_...` |
| colour | `COL_...` |
| text in the game's language | `TEXT_...` |
| a single bit | `FLAG_...` |

`0` and `1`, array sizes, and the player count do not need a name.

## 19. Say what a string is, in a comment

Imported string names (rule 12) are unreadable on purpose — they are built from the address. Put the real
text above the line, so a reader knows what the game shows.

```cpp
// no
strcpy(..., MACRO_CALL_MEMBER(...)(DE::SHCDE::TEXT_ALLIES2, 1));

// yes
// "Goods received from ally"
strcpy(..., MACRO_CALL_MEMBER(...)(DE::SHCDE::TEXT_ALLIES2, 1));
```

**neutral** — it is a comment. Both forms are already used on `main`
(`shareGoldAmongTeamMembers`, `UpdateUnitLossSpeechFeedback`).

## 20. `continue` keeps a loop flat

When the rest of the loop should only run in some cases, skip the other cases with `continue`. Do not put
the rest of the loop inside an `if`. This is the same idea as an early `return`, inside a loop.

```cpp
// no — the body moves one step to the right, and keeps moving
for (int basenameStart = basenameEnd - 1; basenameStart >= 0; --basenameStart) {
    if (_resourceName[basenameStart] == '\') {
        ++basenameStart;
        ...
    }
}

// yes
for (int basenameStart = basenameEnd - 1; basenameStart >= 0; --basenameStart) {
    if (_resourceName[basenameStart] != '\') {
        continue;
    }
    ++basenameStart;
    ...
}
```

**measure.** This moves code, so it can move the match. 343 `continue`s across 111 files say it is usually
fine, but check the number on the file you touched.

## 21. When the ugly form is needed, write down why

Sometimes the readable form does not match and the strange form has to stay. Leave one line saying so.
Without it, the next person "fixes" your code and loses the match again.

```cpp
// Strangely only produces matching code if not using "this"
MACRO_CALL_MEMBER(SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(enums::SND_STR_SPEECH_1);
```

Use `fixme:` when the code is wrong but matching, and say what is wrong:

```cpp
// fixme: NOTE: the original performs the exact same food check a second time, it cannot be removed
```

**neutral.** A comment costs nothing, and this is the cheapest way to stop the same work being done twice.

## 22 Prefer descriptive code
```cpp
// no
if ((uint)(playerID - 1) > 7)

// yes
if (playerID < 1 || playerID > 8)
```

Generally **neutral**.

---

## Measuring

Nothing here is worth trusting unmeasured, and two tools disagree often enough to matter.

```sh
cd tools/reimplementation-helper/batch
python build_quiet.py && python reccmp_report.py --run save base.json   # before
# edit
python syntax_check.py                                                  # seconds, catches a bad rewrite
python quick_diff.py <files>                                            # ~6s/file, ranks variants
python build_quiet.py && python reccmp_report.py --run cmp base.json     # the number that counts
```

- **`reccmp_report.py` is authoritative**, and its *second* column (normalized, call targets ignored) is
  what "100% Reimplemented" means.
- **`quick_diff.py` is for ranking variants of one file**, not for judging a file in absolute terms. It
  compiles without LTCG and without the real link, so on some functions it disagrees with reccmp outright:
  `handleActivateTacticalPowers` measures 67 original instructions against 128 of ours and a 0.6462 ratio
  while reccmp calls it a full match. Compare a file against *itself* before and after a change, and never
  read a `quick_diff` ratio as a percentage.
- Its `ret` against `ret 0x0` lines are a disassembler artefact on both sides. On a three-instruction
  function they drag the ratio to 0.6667 and mean nothing.
- `build.bat` exits 0 on a failed compile, so an unchanged percentage is the symptom of a build that never
  happened. `build_quiet.py` exits non-zero instead — use it.
- Resolver flags are not committed. `enable_local_functions.py` has to be re-run after any
  `git checkout -- src/OpenSHC`, and a resolver left `true` with no `.cpp` in the build list is an
  unresolved external at link time.
