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

## 0. Run clang-format on cpp files
This style check changes the cpp files to match the repo style. It is necessary for cpp files to be merged on main.
The rules below are not covered by clang-format.

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

Generally **neutral** but watch out for a return statement including arithmetic that is meant to lead to a 1 or 0.

## 3. Remove casts that are non-destructive and casts that are redundant

```cpp
short first500BuildingsPerPlayer[9][500];

// no
this->first500BuildingsPerPlayer[owner][idx] = (short)buildingID;

// yes
this->first500BuildingsPerPlayer[owner][idx] = buildingID;

// no
int x = (short) this->first500BuildingsPerPlayer[owner][idx];

// yes
int x = this->first500BuildingsPerPlayer[owner][idx];
```

**neutral**, if the cast type is the same as the field type and if a smaller type (e.g. short) is assigned to a larger type (e.g. int).
In case of uncertainty, check the matching.

## 4. `sizeof` instead of a byte count — but only when it is provably the same

```cpp
// no
fillMemory_ByteValue(14836, '\0', &this->playerDataArray[playerID]);

// yes
fillMemory_ByteValue(sizeof(this->playerDataArray[playerID]), '\0', &this->playerDataArray[playerID]);
```

**neutral**, and it binds the call to the layout of the structure.

**Verify the arithmetic before every single substitution.** If the size of substitution does not match the value from the original binary then the referenced struct header likely needs an improvement.

## 5. Integer flags that only hold 0 or 1 are `BOOLEnum`, and are tested in if-statements as such

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

**neutral** — `BOOLEnum` is `int`, so the matching doesn't change.

Prove the claim before making it. The test is *every* store, not the name:

- a **local** whose stores are all `0`/`1` is provable by reading the function body.
- a struct field is provable if all lines of all functions that refer to the field are read.
- a **counter** or **enum** keeps its comparison like it was.

So `!= 0` is not something to be removed without checking.

## 6. `const` on a local that is assigned once

Written **after** the type, as is convention in this project:

```cpp
// no
int owner = DAT_BuildingsState::instance.buildings[buildingID].owner;

// yes
int const owner = DAT_BuildingsState::instance.buildings[buildingID].owner;
```

**measure.** It is generally neutral, but `const` is exactly the kind of extra information
that lets MSVC change how it deals with the constant value. Perhaps it is not assigned a register anymore,
and that changes the whole stack layout or register allocation.

A local does not qualify for this rule if anything later assigns it, steps it (`++`, `--`, `+=`), or takes its address.
Loop counters never qualify. A `const` that has to be removed again later to accommodate a fix is worse than
no `const`, so prefer it on reads of state that the function plainly only reads once.

## 7. Resolve a pointer into a field or an array access

Ghidra turned field walks into pointer arithmetic, and the offsets it left behind can point into a
completely different member.

```cpp
// no — [0x1b] is not this array at all, it is currentAIArray[playerID]
int* currentPlayerFullID = &...currentPlayerFullIDArray[playerID];
if (*currentPlayerFullID == -1 && currentPlayerFullID[0x1b] == 0) {
```

**measure** Naming both arrays is the readable form.

```cpp
if (...currentPlayerFullIDArray[playerID] == -1 && ...currentAIArray[playerID] == 0) {
```

> The tools `unptr.py` and `unoffset_matrix.py` repair these common shapes.

## 8. Let the compiler unroll

A body repeated four times with `playerID`, `playerID + 1`, `playerID + 2`, `playerID + 3` is not something
a human wrote. The original's compiler unrolled an ordinary loop, which we should replicate.

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

**neutral** (actually better most of the time). Try the plain loop before writing copies out, and if
a hand-unrolled body is already in the tree, try collapsing it.

## 9. Prefer for-loops everywhere
All do-while and while loops should be rewritten as for-loops.

**neutral** (usually better).

## 10. Declaration order outranks loop shape

A `while` that a `for` would say better can usually become one, see rule 9, but the conversion must not reorder the
declarations, because MSVC assigns stack slots and registers in declaration order.

```cpp
// no — allowedCount is now declared before index, and the two xor instructions swap
int allowedCount = 0;
for (int index = 0; ...[index] != -1; ++index) {

// yes — same order as before, still a for loop
int index = 0;
int allowedCount = 0;
for (; ...[index] != -1; ++index) {
```

> The tool `perm_decls.py` can assist.

## 11. No magic addresses

For example, sometimes addresses are referred in while loops, but in reality, they are not used: looping over the array
with a for-loop naturally reproduces the address in the machine code without the literal address being required in the source code.
```cpp
ptr = &value;
while (ptr < 0x401000) {
    ptr += 4;
}
```

**neutral**

> Note that the relevant data should be set to reimplemented in the Globals/<Global>.hpp file.


## 12. Literal strings should be imported
Literal strings should be replaced with the appropriate entry from:
`src/OpenSHC/string-literals.hpp` or `src/OpenSHC/wstring-literals.hpp`

**neutral** in most cases, if not use `src/OpenSHC/string-macros.hpp` or `src/OpenSHC/wstring-macros.hpp`

## 13. One function per file, and the file is named after it

Almost every `.cpp` on `main` holds exactly one function, except for some functions that are only called by
another function and MSVC needs to see the body of that function as well. The file name is the function
name, or in case of the exception to the rule the main function name is the same as the file name, the
functions that are only called by the main function are suffixed with `_name`.

```text
src/OpenSHC/Game/GameStateStructures/activateTraderState.cpp   -> GameStateStructures::activateTraderState()
src/OpenSHC/IO/ResourceManager/getCurrentResourceCoreNameUnk.cpp -> ResourceManager::getCurrentResourceCoreNameUnk()
```

The folder is the class: a method of `ResourceManager` lives in a folder called `ResourceManager`.

## 14. The shape of a file

Every file has the following template.

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

- the first include is the class or namespace you are working on, written with `../` (773 files do it this way).
- the `// FUNCTION:` line sits directly above the function. **Never change the address in it.**

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

**neutral.** The compiler sees one value either way.

## 16. Give variables a name that says what they hold

The decompiler invents names like `iVar5`, `uVar2`, `local_8`, `bVar1`. These names mean nothing. A reader
cannot guess what the value is, and cannot see when it is wrong. Plus, giving better names detects situations
in which stack variables are reused according to the decompiler, but instead the original code had stack variable
whose lifetime ended before the end of the function and its slot was used by another new local variable.
Replicating the life cycle of stack variables throughout the function is usually key to get a good match with the
original binary.

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

The project already has names for most numbers. Search before you write a number. Some
numbers appear multiple times across enums, choose the right enum. If you can't settle on an enum number,
add a comment and don't write magic numbers in hexadecimals, but in decimals.

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

**neutral**

## 19. Say what a string is, in a comment

Imported string names (rule 12) are unreadable on purpose as they are built from the address. Put the real
text above the line, if known, so a reader knows what the game shows.

```cpp
// no
strcpy(..., MACRO_CALL_MEMBER(...)(DE::SHCDE::TEXT_ALLIES2, 1));

// yes
// "Goods received from ally"
strcpy(..., MACRO_CALL_MEMBER(...)(DE::SHCDE::TEXT_ALLIES2, 1));
```

**neutral**

## 20. Keep nesting low in function bodies and loops

Using `continue` keeps a loop flat and are preferred if the match is not affected.
Prefer early returns in function bodies if execution flow and match is not affected.

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

**measure.** This moves code, so it can move the match.

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

**neutral.** A comment costs nothing, and this is the cheapest way to communicate what has been tried.

## 22 Prefer descriptive code
```cpp
// no
if ((uint)(playerID - 1) > 7)

// yes
if (playerID < 1 || playerID > 8)
```

Generally **neutral**.

## 23 Prefer if-else over ternary
The MSVC compiler optimizes the last branch of a longer if-else chain into an else-statement with a ternary in it, usually when the thing being compared has a limited number of possible values. Extending the if-else chain is more natural code.
```cpp
// no
if (DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel == 0) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 100;
} else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 1) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 90;
} else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 2) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 80;
} else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 3) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 70;
} else {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk
        = (int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 4 ? 60 : 50;
}

// yes
if (DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel == 0) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 100;
} else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 1) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 90;
} else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 2) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 80;
} else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 3) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 70;
} else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 4) {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 60;
} else {
    DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 50;
}
```

**neutral**

---

## Measuring

All style changes that should be measured should use manual before and after checks or the following tools.

```sh
cd tools/reimplementation-helper/batch
python build_quiet.py && python reccmp_report.py --run save base.json   # before
# edit
python syntax_check.py                                                  # seconds, catches a bad rewrite
python quick_diff.py <files>                                            # ~6s/file, ranks variants
python build_quiet.py && python reccmp_report.py --run cmp base.json    # the number that counts
```

- **`reccmp_report.py` produces good match percentages**, and its *second* column is
  what can be considered almost "100% Reimplemented" if reccmp itself doesn't show 100%.
- **`quick_diff.py` is for ranking variants of one file**, not for judging a file in absolute terms. It
  compiles without LTCG and without the real link, so on some functions it disagrees with reccmp outright:
- `build_quiet.py` exits non-zero if compilation failed.
- Resolver flags are not committed. `enable_local_functions.py` and `Enable-Reimplemented-Data.ps1` have to be re-run after any
  `git checkout -- src/OpenSHC`, and a resolver left `true` with no `.cpp` in the build list is an
  unresolved external at link time. Never commit resolvers set to `true` nor local build lists.
