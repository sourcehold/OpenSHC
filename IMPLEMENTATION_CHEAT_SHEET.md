# Implementation Cheat Sheet

This file is meant to contain general behaviors, patterns and oddities of the compiler that are found during the reimplementation process.  
It should be used as a reference for the reimplementation process by providing possible options on how the code can be changed to produce different assembly while keeping the logic flow.  
Update whenever new information is discovered!

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

### Conditionals

Instructions can only be pulled:
- before a condition block if every block has the same instruction at the start.
- after a condition block if every block that does not return has the same instruction at the end.

This also applies when putting instructions inside the condition branches.

### Variable Usage

Naturally, the logic flow needs to be kept, so the update of a variable can not move before or after another usage of the same variable.

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

### Frame Pointers: `optimize("y", off)`, Not `optimize("", off)`

`push ebp` followed by `mov ebp, esp` or `lea ebp, [esp + N]` in the original, with the parameters addressed off
`ebp` and `this` spilled to the frame, means that function was built **with** a frame pointer. Comparisons against a
zeroed register (`xor ebx, ebx; cmp word ptr [..], bx`) come with it and make the whole thing look unoptimised, but
it is not: `#pragma optimize("", off)` took `processMeleeInitiation` from 38.3% to **6.0%** and inflated it from 707
to 1262 instructions against the original's 734. The frame pointer alone is what differs, so disable only its
omission:

```cpp
#pragma optimize("y", off)
// FUNCTION: STRONGHOLDCRUSADER 0x...
...
#pragma optimize("y", on)
```

That took the same function 31.3% -> 39.6% in reccmp with the count landing at 713 against 734.

Two things not to trust here. `orig_asm.py --stats` reports `frame pointer: False` for this case, because it looks
for `mov ebp, esp` and the original uses `lea ebp, [esp + N]`; check the prologue in the diff yourself. And a frame
pointer on *both* sides is not this pattern at all - it is usually forced by stack alignment for a large local array
(`and esp, 0xfffffff8`), as in `selectionContainsCombatUnit`, where there is nothing to change.

What stays out of reach is where `ebp` points. The original sets it into the middle of its frame so every
displacement fits in a byte (parameters at `ebp + 0x7c`), while MSVC gives us `mov ebp, esp` and addresses
parameters at `ebp + 8`. Only two of the 109 functions in `Map::Units::UnitsState` have a frame pointer at all, so
scan for the prologue rather than guessing.

### Handwritten Assembly Without `mov reg, 0`

A handwritten block does not always announce itself with `mov reg, 0`. The other tells are locals stored to the stack
and reloaded by the very next instructions (`mov [esp + 0xc], ecx` ... `mov eax, [esp + 0xc]`), a bare `push`/`pop`
parking a pointer in the middle of the body, and an operand size the element type does not have
(`or word ptr [esi + 1], bx` on a byte layer). `stampOccupancyFlagOnSurroundingTiles` and
`writeSixToTileMap1104InAllDirections` are both that: 20.4% and 22.2% as C++, 100% as a few locals plus one `__asm`
block.

Three things that were believed otherwise:

- A resolver global **can** be named in an asm operand, through the typedef and the struct-member syntax:
  `mov edx, dword ptr [DAT_TileMapState::instance]TileMapState.ptr_MovementDirectionTranslationMatrix`. This assembles
  to the absolute load the original has, so no pointer local is needed for it.
- An `__asm` block does not force a frame pointer. Both functions above stay `esp`-relative, and the compiler tracks the
  `push` inside the block when it addresses the locals after it.
- `processMeleeInitiation` has such a block and a frame pointer, but the frame pointer comes with the block there:
  dropping `#pragma optimize("y", off)` once the block was inline asm was worth 49.7% -> 61.0%, and `lea ebp, [esp - N]`
  then matched by itself.

The C++ locals that feed the block decide the prologue, and their **declaration order** decides which register and
which stack slot each gets. Sweep the permutations (four locals are 24 runs of `quick_diff.py`); exactly one order was
100% in both functions.

### Calls Through the Global Instance

`mov ecx, <UnitsState instance>` in front of a call where we emit `mov ecx, esi` is the same global-instead-of-`this`
pattern as for fields, on a call: write `MACRO_CALL_MEMBER(..., DAT_UnitsState::ptr)`. Fourteen call sites in
`Map::Units::UnitsState` had it. Converting the call usually frees the register that held `this`, so re-check every
field of that function afterwards - several that had been swept to the global form only matched that way *because*
`this` was being kept for the call, and have to go back to `this->` (`deleteUnit` 68.5% -> 98.7%,
`selectSiegeEngineAndPlayFeedback` 85.9% -> 100%, `setDestinationNearTargetedBuilding` 47.3% -> 70.9%).

When the original never forms `[reg + reg + offset]` at all, nothing in the function goes through `this`: convert every
access at once. A per-field greedy sweep cannot find this, because no single conversion pays until the last one frees
the register (`checkTargetBuildingPossibilityOrState` 41.7% -> 100%).

### Jump Tables That Cover More Values Than Our Cases

Compare the table's range, not just its presence: `add eax, -0x16; cmp eax, 0x37` against our `lea eax, [edi - 0x27];
cmp eax, 0x26` means the original `switch` has case labels below ours. Decode the byte table to see which values and
where they go. If they land on the same block as `default`, an explicit `case` with the same body does not bring them
back - the compiler drops it before it builds the table. The arm did something that was optimised away later, and a
dead store reproduces that:

```cpp
case UT_E_ARCHER:
case UT_E_ARCHER_DEBUG:
    _archerScatter = 0; // never read
    return ...;
```

`prepareProjectileTarget` went 53.7% -> 81.5% on this alone, because the wider table also made the switch index the
value the function is left returning. Where the extra value has its own table index, a plain explicit case is enough
(`getPeasantGmID`, `case UT_PEASANT:` in front of an identical `default:`).

### Duplicated Blocks: Being Longer Is Not Evidence

Two identical blocks in the decompiler output are often identical in the original too, and a longer instruction
stream on our side does **not** show otherwise. `setDestinationForUnit` carried two byte-identical 40-line copies of
its climb setup and ran 52 instructions longer than the original; folding them into one block behind a flag brought
the count from 322 to 291 against the original's 270 and still dropped the match from 44.3% to 32.8%. The
convergence in length was not the signal - the original genuinely has both copies.

What did pay was the narrower case where the shared block sits in two `switch` arms that both `break`:
`harassBuildingsWithSiegeAI` had the same ammunition check in its catapult and trebuchet arms, and lifting it out
behind a flag (every `case` kept in the jump table) went 48.3% -> 49.8% with the count moving 237 -> 218 against 223.

So scan for duplicated runs, but treat the result as a candidate list only, and keep a revert-unless-better guard.
Across `Map::Units::UnitsState` six functions had runs of eight or more duplicated lines and only one was wrong:
`applyDragBoxSelectionByPriority` (29 lines), `acquireShootTarget` (22) and `shouldUnitsEngageInMelee` (12) all match
the original's instruction count almost exactly, so their duplication has to stay.

### Global Instance Instead of `this`

An absolute instance address in the original's operand (`[eax + I<...::UnitsState>::instance+2504]`) where our source
reads `this->field` means the original went through the **global instance**, not the `this` pointer. Our `this->` form
compiles to `add eax, ecx` plus `[eax + off]`; the global form keeps the scaled index in one register and folds the
instance address into the displacement, so the whole instruction stream shifts and the match collapses even when the
logic is identical. `getRemainingRequiredEngineers` sat at 65% after its control flow had been fixed and reached 100%
on this change alone; `tryAttackUnitID` went 48.7% -> 100%, `selectionHasUnmannedSiegeEngine` 80% -> 100%.

Find the candidates by scanning `reccmp/dll/diff.json` for functions whose original mentions
`<ClassName>,<address>>::instance+` while the source only uses `this->`, then sweep **one field at a time**,
keeping each conversion only if the measurement improves. Converting a whole function at once is the wrong
granularity and will throw away most of the value: on that basis `computeLadderClimbPath` and
`findNearestEnemyAndHeadTowardsIt` both measured *worse* and were rejected, yet per field they are worth
42.6% -> 86.6% (`pathPlanStart` alone) and 40.1% -> 64.1% (four fields). A greedy cumulative loop over the
distinct fields is enough, but read the size of the rise against `quick_diff`'s own caveat about low ratios. A real
conversion moves it by 0.1 to 0.4. Below about 0.6 absolute, a *small* rise is worthless and often a loss: on
`setMoveDelayForUnitsOnSameTiles` 0.236 -> 0.285 and `selectNewBlessingTarget` 0.470 -> 0.490 both came back WORSE in
reccmp (24.1% -> 23.9%, 40.3% -> 36.1%), while every rise over 0.1 held. Above about 0.9 absolute a small rise is
trustworthy (`applyTunnelDamageAlongPathPlan` +0.013 was really 89.2% -> 96.0%). So: confirm anything under +0.1 with
`reccmp_report.py --run` before committing it, and expect to revert roughly half of them.

Most functions mix the two forms, so read the original's operands rather than guessing. `lea ebx, [esi + G]`
with an absolute `G` next to `lea ecx, [esi + edi + 0x614]` in the same prologue is one function using the global
for one field address and `this` for the array base - that was `computeLadderClimbPath`, where exactly one field
moved. `acquireShootTarget` needed three (`_someX_2`, `assassinsMicroDistanceToEnemyUnk`, `buildingHeight`),
`getRemainingRequiredEngineers` reads `unitType` through `this` and the engineer count through the global.

Where it pays is not simply a matter of size. The long dispatch loops do nearly all their work through `this` and
gain nothing - `updateUnits` and `getUnitStateTextParameterAndResourceType` each yielded under 0.01 across every
field, and converting them wholesale cost 0.54 -> 0.20 and similar. The wins are the small and mid-size helpers
where a handful of named fields were reached through the global.

### Variables

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
- **Declaration order picks registers and stack slots, and the parameter's own slot is one of them.** When only the
  prologue or only `[esp + N]` displacements differ, permute the leading declarations and measure. Five locals are 120
  runs of `quick_diff.py`, about ten minutes. `quick_diff.py` hides stack displacements, so several orders tie at 1.0
  there and still differ in reccmp: `selectNewBlessingTarget` had four such orders scoring 90.7%, 93.3%, 98.7% and
  100%, the difference being which local the compiler put into the dead parameter's slot.
- **An expression the original evaluates before a call has to read memory.** `(4000 - blessedAmount) >> 6` built from a
  local copy of the field is sunk below the call that follows, since nothing forces it earlier; built from the field
  itself it cannot move across the call and lands where the original has it. Test the field, then read it again
  (`selectNewBlessingTarget` 0.67 -> 0.90 in `quick_diff.py`).
- A value kept in the parameter's stack slot and incremented there (`add dword ptr [esp + 0x1c], 1` inside the
  innermost loop) is the parameter being reused as a counter (`isTowerTileOvercrowdedByCurrentPlayer`).
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

Before settling for `!=`, try a `do { ... } while (i < N);`. It also stops the unrolling and keeps the original's `jl`:
`setMoveDelayForUnitsOnSameTiles` had two scans over a 2000-entry array that MSVC unrolled five times as `for` loops
(240 instructions against 116); `!=` gave 116 with two `jne`, the `do`-`while` gave 116 with nothing left to differ
(24.1% -> 98.3%). The same function had an `int` copy of the array element tested with `<= 0`, where the decompiler
showed the `short` element tested with `< 1`.

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
