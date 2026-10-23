# Implementation Cheat Sheet

This file is meant to contain general behaviors, patterns and oddities of the compiler that are found during the reimplementation process.  
It should be used as a reference for the reimplementation process by providing possible options on how the code can be changed to produce different assembly while keeping the logic flow.  
Update whenever new information is discovered!

reccmp renders the same bytes differently on the two sides, so a diff line is not automatically a mismatch. The
original's side resolves addresses through the `StructResolver`/`trampoline` symbols and prints `__security_cookie`
as `StructResolver::Instance<unsigned int,12141088>::instance`, and it will print a plain immediate such as
`0xffffff` as whatever global happens to live at that address. Eleven functions in `GameSynchronyState` score
between 84% and 98% while being byte-identical for this reason alone. Before working on a function, canonicalise
the `-`/`+` lines (symbols to one token, call/jump targets to one token) and check they are not already equal.

Note, that Ghidra and reccmp use slightly different disassembly styles, so there might be different opcodes generated. Example: JZ (Jump if Zero) and JE (Jump if Equal) mean the same and are the same instruction. So do not get confused.

## Boundaries

Certain instructions work as boundaries between different code segments, preventing reordering of instructions and aiding in identifying the possible structure. 

### Functions

The main boundary. Regular functions use one of the Visual C++ call conventions:

| Convention   | Arg order    | Register args | Cleanup          | Volatile registers | Non-volatile registers |
| ------------ | ------------ | ------------- | ---------------- | ------------------ | ---------------------- |
| `__cdecl`    | Right → Left | None          | Caller           | EAX, ECX, EDX      | EBX, ESI, EDI, EBP     |
| `__stdcall`  | Right → Left | None          | Callee           | EAX, ECX, EDX      | EBX, ESI, EDI, EBP     |
| `__fastcall` | Right → Left | ECX, EDX      | Callee           | EAX, ECX, EDX      | EBX, ESI, EDI, EBP     |
| `__thiscall` | Right → Left | ECX = `this`  | Callee (usually) | EAX, ECX, EDX      | EBX, ESI, EDI, EBP     |

| Type                | Register                |
| ------------------- | ----------------------- |
| 8/16/32-bit integer | EAX                     |
| 64-bit integer      | EDX:EAX                 |
| Pointer             | EAX                     |
| Float (`float`)     | x87 ST(0)               |
| Double              | x87 ST(0)               |
| Large struct/class  | Hidden pointer argument |

Instructions usually are not moved to the other side of a call.
Variables/Globals accessed through pointers have to be considered changed due to aliasing. The compiler can not prove they
are the same, so they would need to be pulled into a register again.

If a volatile register is **NOT** used as return register but still used after the call without it being rewritten,
it is a clean indication of a known function body. The source of the other function was likely in the same file,
allowing the compiler to optimize the register usage.

#### Detecting inlined functions
The compiler (and/or linker) likely inlined some functions. This mainly happens if the compilation unit (in our case
function body) can "see" the contents of another compilation unit (function body). Detecting whether this has occurred
is challenging. So far, we have found one pattern that predicts it (occurs in OpenSHC::Global::WinMain).

The context is the following:

```cpp
inline static void Helper(Menu* menu)
{
    MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, menu)(OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER);
    MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::renderConstructionMenu, menu)();
}

int WinMain() {
    /* The use of the Helper() leads to 100% match. */
    Helper(DAT_MenuHandleState::instance.currentMenu);
    /* Using the lines below would have produced a mismatch: */
    // MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, menu)(OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER);
    // MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::renderConstructionMenu, menu)();
}
```

The pattern in assembly is as follows:

```asm
mov ecx, [ptrData]
mov esi, ecx
call A
mov ecx, esi
call B
```

Which basically means the this-pointer (currentMenu) is saved to esi to restore it easily after the first call.

If there had been no inline function, we would have seen the following pattern instead:

```asm
mov ecx, [ptrData]
call A
mov ecx, [ptrData]
call B
```

Note that the inlined-variant is shorter in size, which causes jmp/je/jg (etc.) to mismatch throughout the whole
function body. Furthermore, esi has been "claimed" to achieve this reduction in code size, so esi is used differently,
which usually also cascades in further code changes.

### Conditionals

Instructions can only be pulled:
- before a condition block if every block has the same instruction at the start.
- after a condition block if every block that does not return has the same instruction at the end.

This also applies when putting instructions inside the condition branches.

### Variable Usage

Naturally, the logic flow needs to be kept, so the update of a variable can not move before or after another usage of the same variable.

The order in which **initialised** declarations appear decides which register each one gets. `countPlayersInSameTeam`
matched instruction for instruction except that the parameter was loaded into `eax` instead of `edx`; moving
`int iVar2 = 0;` in front of `int iVar1 = DAT_GameState::instance.mapAndTime.playerTeams[playerID];` freed `edx`
for the parameter load and took it from 95.7% to 100%. Uninitialised declarations do not have this effect - a
sweep of `quick_reorder.py -s` over the declaration block of 27 functions found no win at all.

Stack *slot* assignment for spilled locals is a different matter and is not reachable from the source. Where the
original lays its locals out in Ghidra order (`local_1c` at the lowest `esp` offset through `local_4` at the
highest) and our build permutes them, neither declaration order, initialisation order, nor renaming changes
anything; this was tried on `setupSkirmishLobby`, `initMultiplayerLobbyState`, `initializeFinalResultsForActivePlayers`
and `createCompoundAddressBasedOnSelectedProvider`. Spend the effort elsewhere.

### Statement Order

The order of instructions in the assembly is not the order of the statements in the original source.
Within a boundary the compiler schedules freely, so do not copy the instruction order into the source.

This matters most for long runs of independent stores into one object, as in `AICState::setAICParameters_NN`:
the whole body is `this->aics[aicIndex].<field> = <constant>;` over ~130 fields, and the compiler emits
those `mov dword ptr [eax + <offset>], <reg>` instructions in an order of its own. Rewriting all 16 of
those functions so their statements followed the original's store order made every one of them *worse*
(e.g. `setAICParameters_14` 82.4% -> 50.0%).

That does not make the order unrecoverable. The compiler moves only the stores whose value sits in a **register**:
when a constant's register is about to be reloaded with another constant, the stores still waiting for the old value
are pulled up in front of the reload, and stores of a newly loaded constant are gathered behind it. Stores of an
**immediate** (`mov dword ptr [eax + off], 0x46`) stay where the source put them. So:

1. Take the immediate stores of the original as the skeleton of the source order. Across a family of sibling
   functions the skeleton is the same template, so vote the precedence of every pair of fields over all siblings -
   a field that is a register store in one function is an immediate in another.
2. Put each register store back at its place in that template (mostly struct order, with the template's own local
   swaps: `unknown002` before `unknown001`, `populationPerFarm` before `unknown011`, `recruitProbDefWeak` before
   `recruitProbDefDefault`, `RecruitIntervalWeak` before `RecruitInterval`, `AttMaxAssassins` before `AttUnit2`).
3. Compile and move the few statements that still sit elsewhere next to their neighbour in the original.

All 16 `setAICParameters_NN` went from 75-95% to 100% this way, with no type or header change; the earlier attempt
failed because it copied the *instruction* order, hoisted stores included. Which constant lands in which register
then follows by itself - it was a consequence of the statement order, not of register pressure.

## Structure

### Bitwise Operations

Decompiler code that contains complex bitwise instructions that can not be explained by flag operations might hint
at the usage of a structure that the compiler optimized.
If not contained in the examples here yet, AI is usually good at identifying them.

The most prominent example are modulo operations so far:
```cpp
if ((int)SEC_RNG.currentNumber1 % 3 == 0) {
    DAT_SoundEffectsHelperData1.field6_0x34 = 1;
}
else {
    DAT_SoundEffectsHelperData1.field6_0x34 = (-(uint)((int)SEC_RNG.currentNumber1 % 3 != 1) & 0xfffffffe) + 2;
}
```
is roughly:
```cpp
int const randomNumber = SEC_RNG::instance.currentNumber1 % 3;
if (randomNumber == 0)
    DAT_SoundEffectsHelperData1::instance.field6_0x34 = 1;
else if (randomNumber == 1)
    DAT_SoundEffectsHelperData1::instance.field6_0x34 = 2;
else
    DAT_SoundEffectsHelperData1::instance.field6_0x34 = 0;
```

Or another modulo:
```cpp
uVar1 = (int)SEC_RNG.currentNumber1 & 0x80000003;
if ((int)uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffffc) + 1;
}
```
being
```cpp
SEC_RNG::ptr->currentNumber1 % 4
```

### Variables

A 16-bit field saved into a `short` temp and written straight back is loaded with `movzx`; the same field saved into
an `int` temp is loaded with `movsx`. When the original sign-extends a `short` field it only reads and restores,
widen the temp rather than changing the struct (`recomputeHashesAndSendResync`, six entity fields, +0.6%).


- Ghidra declares all variables at the start of a function. Please try to declare them when needed. Helps the readability.
- Always prefer direct usage of parameters and member variables over the creation of a local temporary on first attempts. Real local variables are rare.
  - This may even include cases that can get pretty long in our style, like a variable access providing the index for an array.
  - If this does not work and the assembly suggests otherwise, attempt to create a local variable.
- The assembly may contain multiple assigns of the same value to the same variable within the same boundary. This might be optimization suggesting there was only one assign.
- The decompiler may suggest multiple assigns of the same value to the same variable within the same boundary. If this is not present in the assembly, it might be an artifact.
- If a variable is stored in a temporary, before it is directly being incremented or decremented by one, suggests a post-increment/decrement, even more if the temporary is used after this.
- Do not hoist a repeated sub-expression into a local just because it appears several times. `int const halfWidth = barWidth / 2;`
  used at four call sites lost against the original, which recomputes `barWidth / 2` at every use (SHC_3BB0A8C1_0x004B20B0, 67.6% -> 82.4%).
  Write the expression out again at each use and let the compiler decide.
- **A local that only copies a field lets the compiler fold what the original kept separate.** MSVC forward-substitutes
  an expression built from a register value (`int aiType = pd.aiType; ... int aicIndex = aiType - 1;`) into its use, so
  `aics[aicIndex].x` becomes `[reg*0x2a4 + this + (off - 0x2a4)]` with no decrement left. It does **not** substitute
  an expression that contains a memory read across a store, a call or a branch. The original's
  `test eax, eax; je; add eax, -1; imul eax, eax, 0x2a4; ... [eax + ecx + off]` therefore needs the field tested
  directly and read again for the index:
  ```cpp
  if (DAT_GameState::instance.playerDataArray[playerID].aiType == AIT_NULL)
      return FALSE;
  int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
  ```
  `determineAIPlayerHelp`, `determineAIPlayerAttackRequestResponse`, `addUnitToSmallestPatrolTribe`,
  `setCurrentAttackStrength` all went to 100% on this alone. Fifteen other spellings of the index (casts, pointer
  arithmetic, an inlined accessor, in-place decrement, unsigned) all folded - only the missing local matters. The
  same applies to any other decompiler local for a field (`tracker`, `outerPatrolGroupsCount`): reading the field at
  every use took `getTargetableBuildingForPlayerID` from 65% to 100%.
- **A field compared straight from memory and then reloaded was read with two different types.** The signature is
  `cmp dword ptr [esi + off], -1; je ...; mov eax, dword ptr [esi + off]` in the original where we emit one load and
  compare the register. MSVC 14.00 only CSEs two reads of the same expression, and an `int` compare and an unsigned
  array index are not the same expression, so cast the *indexing* use to `(uint)` and keep the compare on the plain
  field:
  ```cpp
  if (this->buildingApproriateGridXPosition == -1)
      return;
  this->heatMaps[(uint)this->buildingApproriateGridXPosition][(uint)this->buildingAppropriateGridYPosition] = ...;
  ```
  `AIVState::aiPlaceWoodcuttershut` went 91.4% -> 100% on that alone. Grep a reccmp diff for `-cmp dword ptr [...]`
  followed by `+mov ..., dword ptr` of the same address; try the cast on the index first, then on the compared operand.
  The cast does nothing when the two uses are already different expressions (`hostChecksLobbyAIVAvailability` keeps
  its `currentAIArray[player]` reload for another reason), so measure with `quick_diff.py` before building.
- **A read through a reference or pointer alias is not merged with the direct read.** `int const& r = arr[i];`
  (or `int const* p = &arr[i];`) followed by `arr[i]` written out is two loads for MSVC 14, while `int const copy =
  arr[i];` is merged with the direct read. This is the lever when the `(uint)` cast above is neutral, i.e. when the
  second use is a plain value rather than an index:
  - the original compares memory and reloads it after a branch (`cmp dword ptr [esi*4 + G], ebx; je ...;
    mov ecx, dword ptr [esi*4 + G]`): keep the test on the field and read the value again through an alias,
    `int const& ai = arr[player]; int const aiID = ai;` (`hostChecksLobbyAIVAvailability`, 68.6% -> 100%, together
    with `int const* const availability = &this->array[aiIndex];` per outer iteration, which gave the original its
    third induction register);
  - the original compares a register to itself (`cmp eax, eax; je`): that is a third clause `arr[player] == ref`
    with `int const& ref = arr[player];` - every spelling of `x == x`, a duplicated `== -1` and the casts fold away
    (`updateBuildingsStateAndUpdateAIBuildingDecisions`, 91.3% -> 100%).
  Our `/FA` listing shows `npad 5` where the original has `jmp` + `lea ecx, [ecx]`; that pair is the pad, not a diff.
- **A constant index held in a local stops the per-struct multiply being shared.** When the original recomputes
  `playerID * 0x39f4` in every basic block (`mov eax, ecx; imul eax, eax, 0x39f4` three times, with `playerID` staying
  in its register) while we multiply once, the array index in the source was a *variable* that the optimizer only
  later found to be constant. With a variable index MSVC factors each access by its own element size
  (`playerID * 0x1cfa` for a `short` array, `* 0xe7d` for an `int` array), so the three accesses are three different
  expressions and nothing is common. Write `int tribeIndex = 11;` and index with it:
  ```cpp
  int tribeIndex = 11;
  if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL)
      return;
  int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeIndex];
  ```
  Eight `AI::AICState` tribe-command functions went from 38-62% to 100% (`setTribe0xbToAggressiveAndAttack`,
  `sendTribeToAttack`, `aiCommandTribe11/13`, ...). The same happens when the index is a field the code has just
  compared against a constant: `pd.aivCurrentPauseIndex == 1 && pd.aivPauses[pd.aivCurrentPauseIndex] > 0`, not
  `aivPauses[1]`. It is not universal - on functions whose index is a loop sum (`aiTribeIDs[166 + i]`) the local made
  things worse.
- A constant kept in a callee-saved register from the top of the function (`mov ebx, 1` before the first branch, later
  `mov [field], ebx`) is a **result variable** initialised at the top and stored once at the end, not two literal
  stores: `int isNotNervous = 1; ... if (cond) isNotNervous = 0; else {...} field = isNotNervous;`
  (`computeNervousness` 77% -> 100%).
- `add reg, -N` where we emit `sub reg, N` or `cmp reg, N` means two constants were merged: the source compared a
  derived value, `aicIndex == 7` with `aicIndex = aiType - 1`, not `aiType == 8`
  (`removeOrganismsAndSetMoveDestinationPairs` 97.9% -> 100%).
- Where two arguments are loaded on either side of a store (`mov ecx, [x]` ... `mov [stance], 1` ... `mov eax, [y]`),
  give each a local and put the statements in that order: `int x = pd.someX; tribe.unitStance = ...; int y = pd.someY;`
  (`makeUnitsGoDefensiveAndBackToSomeLocation` 95.7% -> 100%). Without a store in between, the *declaration order*
  of two such locals picks which one gets `ecx` (`sendUnitsToAttackBreachedCastle` 98.7% -> 100%).
- The opposite does happen for the operands of a single statement: in `SHC_3BB0A8C1_0x00522520` the original evaluates
  `unitID / 16` and `unitID % 16` into locals before the compound assignment. If a `|=`/`&=` statement with computed index
  and mask does not match, give the index and the mask a local each and keep the declaration order the assembly shows.

### Conditionals

- Ghidra's decompiler sometimes uses a number off by one for the condition compared to the assembly. Use the assembly as reference in this case.
- Ghidra's decompiler sometimes inverts the condition in an if-else case and therefore also the blocks. In most cases, the condition and the block order are like the assembly suggests. Only in some cases the order is actually inverted compared to the source:
  - Certain pressure might cause this. This can only be detected through tests.
  - Early returns.
- A condition block wrapping the entire remaining code of the function or loop can often be inverted to an early return or break, increasing readability.
- If a condition suddenly uses a normally signed variable as unsigned value (e.g. `ja` compared to signed `jg`) and most times also contains a subtraction, it suggests a range condition optimization. The actual value was moved to 0 to allow expressing this via a single check:
  - Decomp code example: `DAT_GameCore.missionNumber1to20 - 1U < 0x14`
  - Original (likely): `1 <= DAT_GameCore.missionNumber1to20 && DAT_GameCore.missionNumber1to20 <= 20`
- A two-sided range check that is the whole body of a `BOOL`-returning function is compiled branchless. Write it as one
  expression, `return lo <= value && value <= hi;`, not as nested `if`s with early returns, and use the literals the
  assembly shows rather than a `short`/`ushort` local holding the field (SHC_3BB0A8C1_0x00530FD0, 78.3% -> 100%).
- Which form a boolean result takes is **not** predictable and has to be tried both ways. The folded
  `return (x & MASK) == VALUE;` matched at only 40% for SHC_3BB0A8C1_0x004549C0; spelling it out as
  `if ((x & MASK) == VALUE) { return TRUE; } else { return FALSE; }`, with locals for the computed index and the loaded
  byte, reached 100%. Together with the range-check case above this means: folded expression and explicit
  `TRUE`/`FALSE` branches are two separate candidates, measure both.
- A switch with fewer then 4 cases is often simplified and uses subtractions in assembly to compare the value:
  ```
  MOV          EAX,[DAT_SoundEffectsHelperData1.SEC_Section1079.  volumeLevel]
  SUB          EAX,EBX
  JZ           LAB_0047c029
  SUB          EAX,EBX
  JZ           LAB_0047bfef
  SUB          EAX,0x3
  JNZ          LAB_0047c386
  ```
  Once 4 are reached, the switch is probably converted to a table lookup.  
  This structure shows up as if-else chain in the decompiler, so do not be confused and check the assembly if the conditions are repeated checks of the same value. 
- A switch is in the end just a structure with a scope that allows to jump to certain cases. Inside this scope, other structures are fully legal. This is allowed, for example:
  ```cpp
  switch(value) {
    ++value; // never executed
  case 0: {
      // do something
      break;
  }
      while (value < 3) {
      case 1: {
          // do something
      }
      case 2: {
          // do something
      }
      }
  default: {
      // do something
  }
  }
  ```
  Consider this, should a switch structure arise with strange fallthrough and loops, like SHC_3BB0A8C1_0x004870B0.

### Loops

Loops are very often presented in the decompiler as a pointer being incremented or decremented. The pointer is often created by getting the address to an array before the loop. There is also often a condition variable present that is incremented or decremented with the direction not necessarily matching the direction of the pointer increment.

Example:
```cpp
int _soundIndex = 1;
if (1 < DAT_SoundSystemState.loadedSoundsCountAndIndex_0x316c) {
    int* piVar1 = DAT_SoundSystemState.soundFileCurrSampleNum_0x28c;
    do {
        piVar1 = piVar1 + 1;
        if ((-1 < *piVar1) && (piVar1[0xbda] != 0)) {
            DAT_SoundSystemState.samplePaused_0x31f4[*piVar1] = 0;
            AIL_resume_sample(DAT_SoundSystemState.sample[*piVar1]);
        }
        _soundIndex = _soundIndex + 1;
    } while (_soundIndex < DAT_SoundSystemState.loadedSoundsCountAndIndex_0x316c);
}
```

It should always be attempted to simplify this logic to a default for-block with array index access:
```cpp
for (int soundIndex = 1; soundIndex < this->loadedSoundsCountAndIndex_0x316c; ++soundIndex) {
    if (this->soundFileCurrSampleNum_0x28c[soundIndex] < 0 || !this->samplePaused_0x31f4[soundIndex]) {
        continue;
    }
    this->samplePaused_0x31f4[this->soundFileCurrSampleNum_0x28c[soundIndex]] = false;
    AIL_resume_sample(this->sample[this->soundFileCurrSampleNum_0x28c[soundIndex]]);
}
```

This covers a lot of cases.

Exceptions are:
 - when the logic has not initial condition check before the loop body. This suggests the usage of a do-while loop.
 - when the update parts of the pointer and index are not the last instructions before the loop condition. This indicates manual handling like in a while loop.
 - when it might lack a counter variable and the index loop simply does not match. This case might indicate a pointer increment loop.  
 Another sign for this could be the storing of the start of an array before the array is incremented. The main pointer is then often reset using this temporary. This may should up in opcodes like this:
    ```
        MOV     EDX,   dword ptr [ESP + 0x20] <--
        MOV     dword ptr [ESI + 0xc],  EBX
        MOV     dword ptr [ESI + 0x24], EBX
        MOV     dword ptr [ESP + 0x20], EDX <--
    ```
    Note the seemingly redundant storing. This structure is followed by a loop where the main array is incremented and a temp used to reset it.

If you see a repeating logic structure, that, for example, increments by a value in its logic every repeat,
you might have found an unrolled loop. Therefore, try to reproduce the logic in loop form and see how the compiler behaves.

If GOTOs are present that clearly jump to the start of a loop, but the logic does not allow to do this without a GOTO, for example from a loop inside a loop, you might be able to move the continue or break condition to the outside. Methods could be placing a fitting condition related to the contained loop conditions after the loop or using a boolean flag that then functions as conditional. Both can sometimes be optimized away.

A global used as a running counter alongside the loop index is usually incremented inside the loop, even when its final
value is a constant. Ghidra shows the folded result: `DAT_CurrentUnitSlotID = 2500;` placed around the loop is really
`DAT_CurrentUnitSlotID = 1;` before it and `DAT_CurrentUnitSlotID += 1;` as the first statement of the body. This was
worth the last 8-10% on the whole `Map::Version::UpgradeMapUnitsTo_*` family (0x0053B310, 0x0053B530, 0x0053B570,
0x0053B5E0 all 90% -> 100%).

`!=` as the loop bound suppresses MSVC's unrolling. If the original ends the loop with `jne` while we emit `jl` and an
unrolled body, write `for (int i = 1; i != 2500; ++i)` instead of `i < 2500` (SHC_3BB0A8C1_0x0053B340, 53% -> 91%).

- A loop whose early exit returns the same value as the code after the loop was a `break`, not a `return`. The tell is
  callee-saved registers pushed *after* the loop's entry test and one shared `mov eax, result` behind the loop, where
  an early `return result;` makes us push everything in the prologue (`assignRequiredIdleEngineersToNewTribe`,
  `addEngineersToSelection`, both ~88% -> 100%).
- Do not add a guard the loop condition already expresses. `if (id == 0) return 0;` in front of
  `for (; id != 0; id = next(id))` moved one `push` across a branch; without it the compiler derives the same early
  exit itself and places it where the original does (`aiRequiresExtraOxtethers`). Likewise put the block the
  original keeps inline first: `if (best > 20) { store; return 1; } return 0;` rather than the inverted guard.

- **Several exits that end in the same statement were usually one statement.** MSVC copies a short shared tail
  (a store or a call followed by the epilogue) into each predecessor, so three `mov word ptr [tribe.unitStance], 2`
  + `ret` blocks in the original do not mean three assignments in the source. Writing the assignment once after an
  `if / else if` ladder instead of `stance = X; return;` in every arm changes how often each value is *used*, and the
  use count is what ranks values for the callee-saved registers - so this is the fix when a function matches
  instruction for instruction except that two registers are swapped (`tribeID` in `ebx` and the tribe offset in `ebp`
  on one side, the reverse on the other). `giveMoveCommandToSortieUnits` 79.6% -> 100%, `instructTribe166ToMove`
  81.8% -> 100%, `assignUnitToATribe` 86.1% -> 100% (one `addUnitToTribe(unitID, tribeID)` after the branches
  instead of three calls). When one of the arms must skip a call the others share, a `bool` set in the arms and
  tested once afterwards compiles away and gives the single call site the original has.
- A search loop whose "found a free slot" exit must skip the check that follows the loop has its end test **inside
  the body**: `for (;; i++) { if (i >= count) { if (best == 0) return 0; break; } ... if (free) { best = create();
  bestIndex = i; break; } ... }`. A `for (i < count)` loop with the check after it tests `best` on both paths, and
  duplicating the tail into the create path changes the frame. With the test in the body the compiler rotates it to
  the bottom and lays the blocks out as the original does (`getSmallestPatrolTribe` 65.2% -> 100%). The same
  function needed `int i = 0;` declared *first*, before the other zero-initialised locals, to get the original's
  `xor` order - declaration order did not matter anywhere else it was tried.

- When a loop walks a pointer **and** counts an index, the two initialisers are not interchangeable. The original
  of `broadcastDesyncResyncCommands` sets the index first (`xor edi, edi`) and the row pointer second, where our
  source had the pointer first; swapping the two statements was worth 0.3%. In the same function the original
  starts the walker one element in and advances it at the **tail**, next to the index increment, where the source
  had `do { p = p + 1; ... }` - moving the `+ 1` into the initialiser and the advance to the loop tail took it from
  96.1% to 97.4%.
- A Ghidra temp reused as the index of several unrelated loops costs a spill. `recomputeHashesAndSendResync` shared
  `iVar39` between its hash accumulator and the climb-data loop; giving that loop its own `int _climbIndex` kept the
  index in a register as the original does (58.4% -> 58.8%). Splitting the *other* loops that share the same temp
  changed nothing, so split the loop that the diff points at rather than all of them.
- An early `return <constant>;` is sometimes a fall-through in the original. `addPlayerToCurrentPlayerArray` ends its
  last search loop with `return 0;`, but the original zeroes the slot index and falls into the shared store, writing
  the id into slot 0 before returning it. The tell is a store between the `pop`s of the epilogue
  (`xor eax, eax; pop esi; pop edi; mov [ecx + eax*4 + ...], ebx; pop ebx; ret`) - one epilogue where the
  reimplementation has two.

- `mov edx, esi; add esi, 1` at the **top** of a loop body, with the body then indexing by the copy, is a `while`
  loop that takes the index and advances the counter first: `while (i < count) { int index = i; i++; if (...[index]...)
  { ...; return; } }`. A `for (...; i++)` with the same body does not produce it. Together with `int i = 0;`
  declared where the original's `xor esi, esi` sits (here before an earlier early-return test, which then compares
  against that zero register) this took `generateSiegeCreationInformation` from 39.4% to 100%.

### GOTO

A function may contain multiple GOTOs.
These might be very large condition blocks the decompiler did not wrap.
Often, however, these indicate that the compiler optimized certain branches by reusing the assembly code.

These are very hard to get right, since it is sometimes unclear which parts need to be unified and which code needs to be doubled at different positions.
Another possibility are condition optimizations. If one branch can ensure that the next condition after the block will be always true for it, the compiler may optimize this to a GOTO into or after the next condition block from inside the current branch.  
For example, one of two branches might set the variable that in the required
source will be checked in the next condition. As a result, the compiler may prove that the condition is always true or false.

Despite all these problems, still try to remove the GOTOs.
They might be worth trying in very tricky cases, but they were usually seen as code smell even back then and were unlikely to be present in the code.

### String Literals

String literals are not resolved. Instead we use tow big files, `string-macros.hpp` and `string-literals.hpp`.
`string-macros.hpp` is the ground truth. However, when ever possible, using the pointers from `string-literals.hpp` is preferred.

There is one known case that requires using only the macros:
Only literals can by split up into multiple parts and be moved into registers to copy a string, for example via "strcpy".
In this case, use the macros for the strings and **DO NOT** include `string-literals.hpp`, since this might cause different behavior.
Should a mixture of pointers and macros be required, because the macro to not produce the fitting structure, still only use the macros from `string-macros.hpp`. Create a string pointer in the cpp file and use this for the pointer.

Make always sure to use a reference from this files instead of a direct string literal.

### Blocks and Scopes

Many blocks come naturally with the usage of other structures. However, either by being in the original source or maybe via inlined functions, it can happen that a block is added to the logical function flow.

It is hard to find these cases. I one situation, local variables that were used as local buffers whose pointers were send into functions had the issue of adding to the stack size. The lifetime of such just seems to naturally extend to the end of the block. Wrapping these statements into inline blocks solved this case.

## Functions

### Return Values

A function declared `void` whose assembly still leaves a value in EAX at the return usually returns it. The most common
case is a function that returns the ID it was passed: changing `void EntityState::activateProjectileEntity(int entityID)`
to `int` with a trailing `return entityID;` took SHC_3BB0A8C1_0x004039B0 from 36.4% to 100%. Fix the signature in the
generated header rather than working around the difference.

### Per-file optimization pragmas

`/O2` is a bundle (`/Og /Oi /Ot /Oy /Ob2 /GF /Gy`), and a few translation units in the original were plainly not
built with all of it. Two of its parts are worth testing per file when a function is stuck and the diff shows
structural noise rather than a source bug:

- `#pragma inline_depth(1)` - `/Ob2` inlines things the original did not. `disconnectDPlay` 66.0% -> 87.4% and
  `createCompoundAddressBasedOnSelectedProvider` 54.1% -> 61.2%, `checkMultiplayerLaggingPlayers` 90.6% -> 91.0%.
  Depth 1 beat depth 0 by about a point on both of the first two; depths 2 and 3 are the same as the default.
- `#pragma optimize("y", off)` - with `/Oy` the optimizer may use `ebp` as a general register and cross-jump
  identical epilogues into one. `waitForMultiplayerHost` has two `DAT_HostAnnounced = 1` returns that the original
  keeps separate: 87.0% -> 98.9%. Note that putting `/Oy-` on the command line through
  `set_source_files_properties` does **not** reproduce this; only the pragma does.

Sweep them rather than guess: patch one file at a time, rebuild, and keep the ones that win. Over the 25
non-matching functions of `GameSynchronyState` only four files wanted either pragma, and
`optimize("s", on)`, `optimize("g", off)`, `optimize("t", off)` and `auto_inline(off)` never won anywhere.
Toggling a file in or out of `cmake/compiler-flags-gl.txt` is worth the same sweep - it found one win
(`receiveAllTransmittedCommands`, +1.3) and showed that the `/GL` entries for `determineGameTicksToPerform` and
`computeLatencyAdjustmentFromMatchTimes` currently measure as no-ops.

### Link-Time Code Generation

A volatile register (usually ECX or EDX) that stays live across a call in the original, without being reloaded, means
that call was compiled with LTCG. This is fixable, not a permanent blocker: add the `.cpp` to `cmake/compiler-flags-gl.txt`
so it is built with `/GL`. SHC_3BB0A8C1_0x00504EE0 went from 38.5% to 100% and SHC_3BB0A8C1_0x0045B7F0 to 100% that way.

### Parameters

Parameters might not be pushed like normal in certain cases.
Usually, if two functions are followed by each other, the parameters are pushed for the first function, then the call is executed and then parameters for the second function are pushed. If parameters for the second function are pushed before the first call, it might indicate that the first call was executed in place of a variable, to directly feed the return into the second function.

### Implicit functions

Certain structures produce functions via the compiler that we do not directly call in source.
We simply accept those cases and the mismatches. Although, they should be mentioned in status texts.

- Casts, from and to float values, will produce such functions. `__ftol2` for example converts a float to an integer.
- `security_cookie` structures are placed by the compiler to safeguard against buffer overflows. This protection was active in the original and so it is here. The validation happens through such an implicit function.

### Warnings

The compiler can sometimes generate warnings due to the usage of old (according to MSVC) unsafe C functions.
The assembly and source suggests its usage, however.
In these cases, it is ok to disable the warning with a note at the top of the file.

```cpp
// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)
```

### Intrinsics

Certain functions from the default library are handled differently by the compiler.
They are replaced by specific assembly instructions or otherwise inlined.

A list of all intrinsics can be found in `intrin.h` in the std library, but these are mainly very low level instructions.
However, there are also C functions that can be replaced by intrinsics. The following attempts to extract these from the header:

| Intrinsic | Does                                                                                           |
| --------- | ---------------------------------------------------------------------------------------------- |
| `memcpy`  | Copies a memory block. **Does not support overlapping regions** (use `memmove` for overlap).   |
| `memset`  | Fills a memory block with a byte value.                                                        |
| `memcmp`  | Compares two memory blocks byte-by-byte.                                                       |
| `memchr`  | Searches memory for the first occurrence of a byte.                                            |
| `strcpy`  | Copies a null-terminated C string.                                                             |
| `strlen`  | Returns the length of a null-terminated string (excluding `\0`).                               |
| `strcmp`  | Compares two null-terminated C strings.                                                        |
| `strcat`  | Appends one null-terminated C string to another.                                               |
| `strncpy` | Copies up to N characters from a string; **may not null-terminate** if the source is too long. |
| `strncmp` | Compares up to N characters of two strings.                                                    |
| `wcscpy`  | Copies a null-terminated wide-character string.                                                |
| `wcslen`  | Returns the length of a null-terminated wide string.                                           |
| `ceil`    | Rounds a floating-point value upward to the nearest integer value.                             |
| `abs`     | Returns the absolute value of an `int`.                                                        |
| `labs`    | Returns the absolute value of a `long`.                                                        |
| `longjmp` | Restores a saved execution context created by `setjmp`, continuing execution from that point.  |
| `_setjmp` | Saves the current execution context for later restoration with `longjmp`.                      |

In cases where the decompiler seems to perform one of these actions via simple instructions, one can also try one of these functions.

Example `strcpy`:
```cpp
char* pcVar2 = filePath;
do {
    char cVar1 = *pcVar2;
    pcVar2[0x1127e54 - (int)filePath] = cVar1;
    pcVar2 = pcVar2 + 1;
} while (cVar1 != '\0');
```

Example `strcmp`:
```cpp
int iVar2 = 9;
int bVar7 = true;
char*pcVar5 = pcVar4;
char* pcVar6 = "Null.wav";
do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar7 = *pcVar5 == *pcVar6;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
} while (bVar7);
```

#### Known special cases

- `memset` emits its stores from the **lowest** address upwards. When the original clears two adjacent fields from a
  zero register in the other order, the `memset` is wrong even though the effect is identical: in
  `recomputeHashesAndSendResync` the original clears `field309_0x420` before `field308_0x41c`, and replacing
  `memset(&unit.field308_0x41c, 0, 8)` with those two stores in that order was worth 4 points (54.4% -> 58.4%).
  Check the store order in the diff before reaching for `memset`, and keep it where the order does match - the two
  other `memset`s in the same function both lose 3-9 points when expanded.
- `memset` so far was seen optimizing a "set all bytes to zero" case, if it was smaller then a unknown amount. In all known cases it used `EAX` for this. Would still recommend to try `memset` for cases with a register filling multiple **byte-sized** memory locations.

### CRT Functions

Crusader uses a rather small subset of std functions. The ones we are still resolving are all placed in `OpenSHC\OS.hpp`.
A prominent example are `malloc` and `free`, where it is simply needed to use the games variants during hooking to avoid memory leaks,
since the memory management in the std library is rather complex.

For other std functions, mostly the math functions, we decided to just use the std library directly.

### Copy Elision and Return Value Optimization

The compiler may use copy elision and return value optimization.

The return value optimization may appear if a function returns an object, but instead of putting the whole object on the stack, the function receives a hidden pointer to memory from the caller. This memory is then initialized and the pointer to it is also return.  
The actual function signature will only have the object as value return.

Example in Ghidra:
```cpp
std::string* paths_getDocumentsFolderString(std::string* out, bool param_2);
```

Actual signature:
```cpp
std::string paths_getDocumentsFolderString(bool param_2);
```

This structure can be reproduced. However, this can not be said about the resulting Copy Elision.  
If the value is assigned to another object, the compiler tries to avoid creating a copy.

**This only works if the function is called directly. Any form of indirection via pointer or resolver will not optimize. This is a fundamental limitation of the MSVC2005 compiler.**

As a result, such cases do not use the resolver. The limitation through this is accepted, although, it should be noted in the status entry for the caller.

### Stack

The stack of the function is an important orientation for decompilation.
The reference point is the `esp` register, which points to the top of the stack. The stack grows **downwards** from the top, so actions that grow the stack reduce the `esp` register, for example `push` reduces the `esp` register by 4 and grows the stack by 4.

Naturally, the stack reserved for the function indicated by `sub esp, <number>` at the start and `add esp, <number>` at the end of the function, need to match. This can be achieved by adding or removing locals or shrinking or growing arrays within the logical boundaries of the function. **It must never break the logic**.  
At best, not only the stack fits, but variables are also at the correct positions and sizes within.

If the stack usage shows a proper order in the function (i.e. the initial array occupies the first part in the allocated function stack, which means it requires the highest `[esp + <number>]` to reach), it might be sometimes good to fit one "side" of the stack first and then experiment with the rest of the function that has a non-fitting stack usage.

### A constant that reaches a field through a register was a local in the source

Where several arms of a chain each store the *same* literal both into a field and into an
arithmetic expression, the original loads the literal into a register first:

```asm
mov eax, -0x96              ; the constant, in a register
add ebp, eax                ; popularity = popularityAfterFear + penalty
mov dword ptr [ebx], ebp
mov word ptr [esi + 0x32ff8], ax   ; someCount54 = penalty, from the SAME register
```

Writing the constants out per arm (`popularity = snapshot - 150; someCount54 = -150;`) gives
`mov word ptr [...], -0x96` with an *immediate* instead, because the two uses then share nothing.
The source assigned one local in each arm and used it after the chain; MSVC then duplicated the
two statements into every arm, which is why the stores look per-arm in the asm:

```cpp
int siegePenalty;
if (c <= 0) { siegePenalty = -150; } else if (c <= 5) { siegePenalty = -125; } /* ... */
this->...popularity = popularityAfterFear + siegePenalty;
this->...someCount54 = (short)siegePenalty;
```

This single change took `updatePopularity` from 68.3% to 93.2%; it also fixed the register
allocation of the whole surrounding function, which had looked like an unrelated allocator gap.
The tell is an *immediate* on our side where the original uses a byte/word register (`ax`, `cx`)
that was just loaded with the same constant.

### The struct/loop base anchor moves when a field loses its stores

MSVC picks one address as the base for a run of accesses into the same object
(`lea esi, [ecx + 0x367e4]`, then `[esi - 0x10]`, `[esi + 0xe0]`, ...). Which field lands at
offset 0 is not the most-used one and is not controllable from the source, but it *does* change
when the source changes: introducing a local for a field that was previously stored in several
arms moved the anchor by 0xe0 in `processFoodConsumption` and by 0x10 in
`processPeasantSpawnAndDespawnCycle`, and every displacement in the function then differs.

Both of those locals are provably present in the original (a value survives a call in a
callee-saved register), yet the anchor shift cost more than the local gained:
81.7% -> 61.7% and 85.3% -> 69.0%. So when a `FRAME`-free function regresses by a large,
suspiciously uniform amount after a one-line change, compare the `lea`/`add` that sets up the
base before looking anywhere else, and keep the form with the matching anchor.

### A function that looks huge may be a tail call

`nof_fpoints_locationFinder` had been reimplemented with a 40-line `do/while` body; the original
is eleven instructions ending in `mov ecx, <global>; jmp 0x4a6940`, a tail call to
`PathFindingState::searchCertainPathLayer`, whose body Ghidra had folded into the caller's
decompilation. Check the original's last instruction for a `jmp` to another function's entry
before reproducing a long body: 35.6% -> normalized 100% here.

### The join block of a long if/else-if chain moves with the size of the first arm

In `computeBuildingCategoryEntryPointAndDestroyEarlierBuilding` the chain order, every arm's body and the
shared tail all match the original, yet the original ends
`[prologue][first arm][else chain][tail][epilogue]` and this toolchain emits
`[prologue][first arm][tail][epilogue][else chain]` - the `ret` lands at 51% of the function instead of 99%,
and because reccmp aligns instruction streams, almost the whole function then counts as differing (33.5%).

The flip is a threshold on the **first arm**, not a source shape. Thirteen source forms (switch, fully
nested `else`, combined guard, empty trailing `else`, nested early returns, `__forceinline` helpers for the
tail and for the chain, parameter copies, casts, declaration order) all produced byte-identical code.
Shrinking the first arm does move the tail to the end, and three unrelated shrinks did it: dropping one arm
of its inner `orientation` chain, dropping its three early returns, or dropping its nested
`currentMenuViewType` block. The threshold sits between 168 and 175 instructions for that function, and the
original is 178, so it is not reachable by trimming anything the original actually contains.

`#pragma optimize("s", on)` also produces the original's layout, which is a useful diagnosis - but it is not
the explanation: measured over the thirteen functions still short of 100% in `Game::GameStateStructures`,
`/Os` lost ground on **every single one** (e.g. `showPopAndGoldPopup` 0.93 -> 0.20,
`renderDebugDataCurrentPlayerData` 0.96 -> 0.17). The original was built for speed; only its block layout
differs, which points at a different compiler build rather than a different flag. `/G5`, `/G6` and `/G7`
change nothing in this toolchain (they are deprecated no-ops in VS2005).

### The struct base anchor is coupled to the transformation you are trying to make

MSVC bases a run of accesses into one object on a single address (`lea esi, [ecx + 0x367e4]`, then
`[esi - 0x10]`, `[esi + 0xe0]`, ...). Which field lands at offset 0 is not a size or frequency decision -
with the right anchor `processFoodConsumption` gets 30 byte-sized displacements and with the wrong one 3,
and MSVC still picks the wrong one - and it cannot be steered from the source: the global vs `this->`
spelling of a field, an extra read of it, the index's cast, the statement order and the number of stores to
other fields all leave it unchanged (probed with a `/FA` compile per variant, about ten seconds each).

What *does* move it is the very change you want:

- `processFoodConsumption`: the original keeps `currentPopulation * 3` in a callee-saved register across the
  `isAIPlayer` call, so a local is provably right. Writing that local - or getting the same CSE for free by
  enabling LTCG over the callee - moves the anchor by 0xe0 and costs 20 points, more than the local gains.
- `processPeasantSpawnAndDespawnCycle`: the original stores `vclockIncrement` once after the chain rather
  than in each arm. Hoisting the store moves the anchor by 0x10 and costs 15 points.

Both originals have the local *and* the matching anchor, so the combination is simply not reachable here.
When a one-line change costs a large and suspiciously uniform amount, read the `lea`/`add` that sets up the
base before looking anywhere else.

One narrow rule did hold, for a condition that reads two arrays of the same struct: MSVC anchors the
induction variable on the **second** array mentioned in the source, while the comparison order follows the
source. `showPopAndGoldPopup` and `createStatsPopUpEntities` need `currentPlayerFullIDArray` tested first
*and* used as the anchor, so the two requirements conflict and the faithful form (the one the asm's
comparison order shows) is the one that loses the anchor.

### Check whether the original shares a tail before duplicating a call

Ghidra renders a cross-jumped tail as a `goto` into the middle of another branch, and the shared part can be
a single instruction. In `processPeasantSpawnAndDespawnCycle` the two `playSpeechSFX` sites are one call
reached from both paths with the speech ID in a register (`speechID = SEID_POP_EMIGRATE; goto LAB_0045b684;`),
and in `updatePopularity` the six siege arms share `popularity = snapshot + penalty; someCount54 = penalty;`.

The two need opposite treatment, so read the asm rather than the decompiler's shape:

- `updatePopularity` had to *gain* the variable: MSVC then duplicated the two statements into each arm by
  itself, which is what the original does, and the function went 68.3% -> 93.2%.
- `processPeasantSpawnAndDespawnCycle` already emits one call site - MSVC cross-jumped the two identical
  tails on its own - so routing the ID through a `SpeechEffectID` local changed nothing (MSVC propagates the
  constant straight back into the push). Count the call sites in a `/FA` compile before restructuring.

### Declaration order decides stack slots, and two swapped locals cost a whole function

MSVC assigns stack slots in declaration order. Two locals declared the wrong way round therefore sit
in each other's slots and, because the slot drives the spill and reload, usually end up in each
other's registers as well. The damage spreads over every instruction that touches either of them,
while `diff_triage.py` still calls the function register-naming only - `assignSelectionToKey` read
95.9% with a `norm` of 1.000.

`diff_slots.py` is the detector: the same number of slots on both sides with a different use count
per slot. For `assignSelectionToKey` the original spills
`mov [esp+0x18], edi; mov [esp+0x1c], ebx; mov [esp+0x20], esi` and reloads in the same order, so the
local in the lowest slot is declared first. Our source had

```cpp
int slotID = 0;        // -> [esp+0x20]
int tribeIndex = 0;    // -> [esp+0x18]
```

and swapping the two declarations put both the slots and the registers back: **95.9% -> 100%**, one
line moved. `perm_decls.py` automates the search over a short run of declarations. It also found a
field store that belonged after the declarations in `updatePopularity` (93.2% -> 93.9%), and nothing
on seven other functions - so run it on anything `diff_slots.py` flags, but do not expect a hit
everywhere.

### `lea` where the original has `add` means a snapshot local the original did not keep

`field = snapshotLocal + delta` has to preserve the snapshot, so MSVC emits
`lea ecx, [eax + ebp]; mov [field], ecx`. `field = field + delta` lets it update the register that
already caches the field read: `add ebp, eax; mov [field], ebp`. The two differ by one byte per site
and by the register the result lands in, which looks exactly like allocator noise in the diff.

`updatePopularity` spent the whole pass at 93% on six such sites:

```cpp
int popularityAfterFear = this->playerDataArray[playerID].popularity;   // the original has no such local
...
this->playerDataArray[playerID].popularity = popularityAfterFear + siegePenalty;   // -> lea
this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + siegePenalty;  // -> add
```

Dropping the local took it to **100%** (and the six `lea`s were also why every jump offset after them
was 6 bytes off). The snapshot was redundant anyway: nothing between the read and the use writes
`popularity`, which is the condition to check before removing one. The original still loads the field
into a register early - that is MSVC hoisting the read, not evidence of a local.

Note that the sibling line in the same function, `popularity = popularityAfterTax + popularityChange`,
*does* match with its local, because there the original really does keep a separate snapshot. Decide
per site from the `lea`/`add` in the original, not from the shape of the neighbouring code.

### Two arrays of one struct in a condition: the original reaches the second off a pointer to the first

`showPopAndGoldPopup` and `createStatsPopUpEntities` both guard their player loop with

```cpp
if ((currentPlayerFullIDArray[playerID] == -1) && (currentAIArray[playerID] == 0)) { continue; }
```

and both sat at 87-89% because MSVC based the loop's induction variable on `currentAIArray` while the
original based it on `currentPlayerFullIDArray` - four instructions, but they are the pointer set-up,
both guard reads and the loop's end compare, so they carry the whole loop with them. No spelling of
the condition moves it: swapping the operands fixes the base and breaks the comparison order, and
nine other forms (nested `if`, De Morgan, casts, `ptr->`, a local for either read) compile identically.

The decompilation says why. The original walks one pointer and reaches the second array off it:

```c
_currentPlayer = DAT_GameSynchronyState.currentPlayerFullIDArray + 1;
...
if (*_currentPlayer != -1 || _currentPlayer[0x1b] != 0) { ... }
_currentPlayer = _currentPlayer + 1;
```

`0x1b` is the distance between the two arrays in ints. Writing that - a pointer local for the first
array with the second read as `currentPlayerFullID[0x1b]` - took **both functions to 100%**. A pointer
local for the first read *alone*, with the second still by name, changes nothing: both reads have to
go through the one pointer. Keep the magic index, with a comment; it is the only form that matches.

### Three shared-tail rewrites that the decompilation justifies and that still measure worse

The decompilation shows a shared tail for all three of these, and reproducing it without `goto` lost
every time. Read them before spending a day on the same idea:

- `processFoodConsumption` has **one** `processResourceLoss` call with the type in a variable where we
  write four calls with literal types. Setting a `ResourceType` and calling once after the loop is
  exactly the original's shape and measured **83.7% -> 59.7%**: the extra local swaps the zero
  constant and the loop counter between `ebp` and `ebx`, renaming twenty lines.
- `computeBuildingCategoryEntryPointAndDestroyEarlierBuilding` has one `destroyBuilding` call shared by
  five arms and one `buildingEntry` read shared by nine. Hoisting both (an `existingBuildingID`
  variable plus one `category != CAMPGROUND` re-test) lands within one instruction of the original's
  length, 177 against 178, and still loses: the join block stays in the middle, so the alignment does
  not recover.
- `resetVariousCountsAndStatisticsAndStartGoodsAndResources` has one `startResources[0xf] = gold *
  multiplier` store shared by the human and AI arms. Writing the table value into a local in each arm
  so the tails are identical text does not get MSVC to cross-jump them (92.4% -> 91.0%).

A pointer local is not a general fix for the base anchor either: `PlayerData*` locals leave
`processPeasantSpawnAndDespawnCycle`'s anchor to move with the shared store exactly as before, and in
`spawnMotherOrChild` they remove the three `global - this` slots the original has, taking the frame
further from `sub esp, 0x18` rather than closer.

### Read the decompilation, not only the disassembly, before calling a function allocator-bound

Four of the finds above came from `decompile_function`, not from the interleaved reccmp diff, and two
of them were worth 100%. The decompiler names the original's locals and pointers, which is exactly the
information the asm hides: `processFoodConsumption`'s AI branch is
`(currentPopulation * 180) / 100` with `currentPopulation` as the local, not
`(foodClockSpeed * 60) / 100` - the same value, but MSVC reaches the original's instruction sequence
only from the first spelling. `updateCrowding`'s pointer is anchored at `currentPopulation`, which is
why its base is 0x2100 away from the field it stores to.

## reccmp can score a byte-identical function below 100%

`renderDebugDataCurrentPlayerData` scores 96.0% and every single one of the 41 diff lines is this:

    -push I<OpenSHC::Map::Buildings::BuildingsState>::instance+424671 (OFFSET)
    +push 0xffffff

Both sides are the same four bytes. `0xffffff` is opaque white, a colour argument to the text calls,
and reccmp renders it as an address because in the *original* image that value lands inside
BuildingsState; in ours it does not. Verified with `disassemble_function 0x0045A060`, which shows
`PUSH 0xffffff` throughout. The function is byte-identical to the original and no source change can
raise its score. `tools/reimplementation-helper/batch/diff_falsesym.py` finds this class; it is the
only function in GameStateStructures affected, so nothing else below 100% is a tooling artifact.

The reverse mistake looks the same in the diff and *is* a real bug: an operand that should be an
address, written as a literal in our source. Always confirm against the original disassembly.

## spawnMotherOrChild: ebx goes to the anchor instead of the loop counter (54.6%, closed)

The whole gap is one allocator decision. The original keeps `spawnBudget` in `ebx` and the
`playerDataArray` anchor in scratch `edx`, reloading it after calls. Ours does the opposite: the
anchor takes `ebx` (callee-saved, so it survives `spawnUnit` without a reload - arguably better
code) and `spawnBudget` spills, which is the 7th stack slot and the `sub esp, 0x1c` against the
original's `0x18`. Use that frame size as a free oracle: `0x18` means the counter stayed in a
register.

Measured and ineffective - all four produce a *byte-identical* instruction stream to the current
form, so the shape is canonicalised before allocation:

* `int buildingID = 0;` before the budget, as the decompilation has it, with an empty `for` init
* `spawnBudget` declared outside the `playerID` loop (a longer live range does not buy a register)
* both of the above
* both, with `buildingID` also at function scope

Spelling the inner-loop `popularity` read as `this->` instead of `DAT_GameState::instance` *does*
reach the original's `sub esp, 0x18`, because it drops the `0xfffcf0ec` base to one register instead
of two - but that base exists in the original, so the frame matches by compensation and reccmp
measured 54.5%, a slight regression. quick_diff ranked it 0.751 over 0.739; trust reccmp.

## spawnPoisonCloudsAroundBuilding: the memory decrement (92.4%, closed)

The only gap is the loop tail. The original folds it to a read-modify-write plus a fresh re-read:

    sub dword ptr [esp + 0x10], 1
    cmp dword ptr [esp + 0x10], 0

while we keep the value in a register (`mov eax, mem; sub eax, 1; test eax, eax; mov mem, eax`). The
peephole needs the load/sub/store contiguous, and our scheduler puts the `test` between the sub and
the store. The two `continue`s force the decrement into the `for` header, so the obvious forms were
already known to canonicalise; rewriting the `continue`s as nested `if`s to put the decrement at the
bottom of the body - the decompilation's own shape, and the one the peephole wants - measured
*worse* (0.905 against 0.950) and still did not produce `sub dword ptr`.

## processPeasantSpawnAndDespawnCycle: do not hoist the popularity read (84.0%, closed)

The original computes `popularity / 500` twice, once per arm. Hoisting it into one local and taking
the shared `vclockIncrement` store - the `processFoodConsumption` fix, applied here - moves the base
anchor from `0x347a4` to `0x36978` and drops the score from 0.92 to 0.68. The duplicated division is
load-bearing: it is what keeps the anchor on `vclockIncrement`.

## A per-file /Os does not reach the block layout (disproven)

`cmake/compiler-flags-gl.txt` sets `/GL` per file, so the same mechanism can carry any flag:

    file_dependent_read_list(".../compiler-flags-os.txt" COMPILER_FLAG_OS_FILES)
    set_source_files_properties(${COMPILER_FLAG_OS_FILES} PROPERTIES COMPILE_OPTIONS /Os)

That looked like the way to give `computeBuildingCategoryEntryPointAndDestroyEarlierBuilding` the
original's basic-block layout without the cost a global `/Os` was measured to have. It does not
work. With `/O2 /Os`, and then with `/O2 /O1`, the reccmp diff for that function is identical to
`/O2` alone - all 297 lines, 33.5% / 32.8% every time. The `.obj` hash does change, which is
misleading; it is the command line recorded in the debug section, not the code. MSVC resolves the
trailing size flag to nothing more than `/Os` over `/O2`'s `/Ot`, and that bit does not move this
function's layout.

So the earlier "`/Os` reproduces the layout" note was a whole-build effect (different inlining
elsewhere), not something a per-file flag can reach. The layout difference - the common tail of the
if/else-if chain laid out after the first arm, which turns the leading `jne` into +0x136 where the
original has +0xb4 and so changes every displacement after it - remains unreachable from the source
or from per-file flags.

## /GL does nothing for a function that makes no reimplemented member call

`computeBuildingCategoryEntryPointAndDestroyEarlierBuilding`,
`processPeasantSpawnAndDespawnCycle`, `spawnMotherOrChild`, `spawnPoisonCloudsAroundBuilding` and
`updateCrowding` were never in `cmake/compiler-flags-gl.txt`. Adding all five changes nothing: every
score in the build list is identical to the digit and the average stays at 97.76%. `/GL` earns its
place by removing the redundant `mov ecx, offset` before a call into another reimplemented method,
so it can only pay where such a call exists and the callee's resolver is on. `updateCrowding` has no
calls at all, and the others call out to methods that are not in the build list. It does not
re-roll register allocation inside a function, which is what these five actually need. Do not add
entries to that list speculatively - measure, and leave it out when the number does not move.

## resetVariousCountsAndStatisticsAndStartGoodsAndResources: a one-byte encoding (92.2%, closed)

The original loads the current player's slot into `edx`, we use `eax`:

    -mov edx, dword ptr [GameSynchronyState::instance+1089140]   imul edx, edx, 0x39f4
    +mov eax, dword ptr [GameSynchronyState::instance+1089140]   imul eax, eax, 0x39f4

`mov eax, [abs]` is the one-byte-shorter `A1` form, so our version of that line is a byte shorter,
which moves the alignment padding before the `startResources` copy loop (the original pads with a
three-byte `lea esp, [esp]`, we emit `jmp 0x3` over a `lea ecx, [ecx]`) and renames a register in
the `_memset` call set-up. One encoding choice, three diff hunks. Spelling the index as its own
local, taking a `const PlayerData*` to the source player, and reading through `this->` instead of
the global all produce a byte-identical function (the `this->` form measures worse, 0.819 against
0.924). MSVC picks the destination register for a load it is about to overwrite, and the source
cannot name it.

## The /GS security cookie is a permanent ~4% floor

`playWAVSFX` (96.2%) and `playSpeechSFX` (96.4%) are finished. Their entire remaining diff is the
`/GS` stack-cookie code that MSVC adds around a function with a large local buffer:

    -mov eax, dword ptr [StructResolver::Instance<unsigned int,12141088>::instance (DATA)]
    +mov eax, dword ptr [__security_cookie (DATA)]
    -call <OFFSET12>
    +call __security_check_cookie (FUNCTION)

Each module gets its own cookie, so the original reads the game's at 0x00B94220 and we read our
DLL's. The `__security_check_cookie` call normalizes away; the cookie *load* does not, which is why
both sit at normalized 96.0% and cannot go higher. Any reimplemented function with a stack buffer
big enough to trigger `/GS` carries the same floor.

The project already declares the game's cookie - `Globals/MSVC_SecurityCookie.hpp`, address
0x00B94220 - and `src/symbols/data.asm` can publish absolute symbols (`SYM EQU 00B94220h`), so
redirecting the compiler's reference looks like it should work. It does not:

    PUBLIC ___security_cookie
    ___security_cookie EQU 00B94220h

    LIBCMT.lib(gs_cookie.obj) : error LNK2005: ___security_cookie already defined in data.asm.obj

The CRT owns that symbol. Getting past it needs `/FORCE:MULTIPLE` on the whole link, with undefined
symbol selection, and the `OpenSHC.exe` target would then read a cookie at an address that only
exists inside the game's process. Not worth 4% on two functions - but note `/GS-` is *not* the
answer either, because the original has the cookie code and dropping it loses more than it gains.

`playSFXAtLocation` is likewise done at 98.1% / normalized 100%: its only diff is the call targets
of the CRT helpers `_CIsqrt` and `_ftol2_sse`.

## updateCrowding: the anchor and the store count cannot both be had (37.7%)

Correcting an earlier note that said the anchor was wrong here - in the current one-store form the
anchor is **right**. The original (`disassemble_function 0x00458E60`) is:

    add ecx, 0x368b4              ; anchor on currentPopulation, displacement 0
    mov ebx, 8                    ; a countdown, no playerID
    xor edi, edi                  ; a zero register, before the loop
    mov esi, dword ptr [ecx - 0x210c]     ; populationCap
    mov eax, dword ptr [ecx]              ; currentPopulation
    ...
    mov dword ptr [ecx - 0x2100], edi     ; crowding = 0, four stores, one per arm
    ...
    add ecx, 0x39f4
    sub ebx, 1
    jnz

We match the anchor, the countdown, the pointer stride and both reads. The gap is that the original
assigns the *field* in each of the four arms, where we compute into a local and store once. The two
forms measure:

* one store, value in `eax`  -> **37.7%**, anchor `0x368b4` correct
* four field stores          -> 33.3%, anchor moves to `0x347b4`, i.e. onto `crowding` itself

The four stores drag the anchor because our zeros are immediates (`mov dword ptr [ecx], 0`), and an
immediate store is shortest at displacement 0, so MSVC bases on the field being stored. The original
pays nothing for a displacement because its zero is in `edi`, which is also why it can spell
`currentPopulation <= 0` as `cmp eax, edi` instead of our `test eax, eax`. Giving the zero a name to
force it into a register does not work - MSVC constant-propagates it straight back to an immediate:

* `int noCrowding = 0;` inside the loop, used as the store source -> 33.3%
* the same declared before the loop, live range spanning it       -> 33.3%

So the choice is the correct anchor or the correct store count, and the anchor is worth 4.4 points
more. Keep the one-store form.
