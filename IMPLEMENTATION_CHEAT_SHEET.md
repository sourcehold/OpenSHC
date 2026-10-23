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

Stack *slot* assignment for spilled locals is a different matter: it follows the **reference weight** of each
local, not the order they are declared in. Neither declaration order, initialisation order, nor renaming moves a
slot - that was observed on `setupSkirmishLobby`, `initMultiplayerLobbyState`,
`initializeFinalResultsForActivePlayers` and `createCompoundAddressBasedOnSelectedProvider`, and the compiler
itself says why. `ColorStackElements` (`P2/stack.c`, which the retail `c2.dll` names in its own assert at line
1372) builds one 28-byte record per stack element holding the local's size rounded up to 4 and its accumulated
reference weight, sorts the records with `StkColorCmp`, and then hands out offsets in that order:

```c
// StkColorCmp, c2.dll 14.00.50727.762
if (a->class != b->class)                  // byte at +0x18, unsigned
    return (a->class > b->class) ? (dir ? +1 : -1) : (dir ? -1 : +1);
ka = (a->weight * 1000) / a->size;         // +0x0C scaled, divided by +0x08
kb = (b->weight * 1000) / b->size;
return ka == kb ? 0 : (ka >= kb ? +1 : -1);
```

So for a homogeneous block of same-class scalars the layout is **descending weight per byte**, and the only lever
on it from the source is how often, and at what loop depth, each local is read. In
`planToBuyWhenLowOnResourceAndSnoozeBuildings` the eleven colored `int` locals come out exactly in that order
(reference counts 5 5 4 4 4 4 4 3 3 3 from the lowest `esp` offset upward) with their declaration positions
scrambled (the 4th declared sits between the 8th and the 9th, the 1st sits last). Adding a single reference to one
of them reshuffled the whole table - another local left the stack for a register entirely - and the new layout was
again exactly monotone in weight. Renaming is inert, as the comparator never looks at a name: `allowQuarries` ->
`zzz` and `allowWoodcutters` -> `aaaaaaaaaa` left the function byte-identical.

Three consequences for reading a diff:

* A slot-order mismatch means our locals carry **different reference counts** from the original's, so look for a
  read the original has and we do not. It is not a declaration-order problem.
* Weight **ties** are left to the order the symbols arrive in, permuted by `QSortColors`, which is an unstable
  quicksort. That is the whole reason `perm_decls.py` took `assignSelectionToKey` from 95.9% to 100% once and does
  nothing in most functions: permuting declarations can only decide ties.
* Locals with disjoint live ranges **share** one slot, and a local can be placed on the slot of a parameter that
  is already dead (`writeMapOrSaveFile` puts eight locals on the first parameter's slot). A slot count is therefore
  not a local count, and Ghidra's "repurposed parameter" rendering - `playerID = 0` used as a loop counter in
  `aiRecruitUnits` - is this reuse, not something the original source wrote. Transcribing it back cost 7 points.

`slot_weight.py` prints this table for one function, with the original's slot census beside it. The primary key,
the class byte at +0x18, is not yet decoded, so arrays and address-taken locals interleave for reasons the tool
cannot currently explain - treat a non-monotone report as a hint, not a contradiction.

About **registers** two things are established and a third is not. A set in this compiler is a 64-bit bitvector
with set/clear mask tables indexed by `n & 0x3f`, and the iterator that hands out members takes the **lowest set
bit** and clears it, so a set is always walked in ascending order:

```c
// c2.dll 0x10b04fa0, "next member of a register set"
for (; (set >> bit & 1) == 0; bit++) {}   // low dword first, then the high one
return set_base + bit + dword_offset;     // and the bit is cleared, so the next call advances
```

`.rdata` holds the register names in three parallel 4-byte-stride tables terminated by `"noreg"`, which gives the
numbering - the **reverse** of the x86 encoding order:

```
edi=0  esi=1  ebp=2  esp=3  ebx=4  edx=5  ecx=6  eax=7
```

What does **not** follow is that physical register choice is "the lowest-numbered free register". That iterator
is a *generic* bitset iterator: where its use could be observed it was walking sets of symbols, not registers
(`ColorStackElements` feeds its result straight into a symbol array as `DAT_10d0faa4 + n * 4`), and tracing one
function's allocation under a debugger returned members numbered 0 to 40 across 140 distinct set objects - a
symbol or pseudo-register space, not the eight GPRs. The numbering above is real and the ascending-order mechanic
is real; which physical register a value ends up in has not been traced to a rule. `Spillcosts` is 854 lines of
live-set bitvector work with no cost arithmetic in it, which at least suggests the cost model decides *who gets
spilled* rather than *which register a winner gets*.

So treat a register mismatch as an interference difference - a different set of values was live at that point -
but as a working hypothesis rather than a decoded rule. The lever is still where each value is born and dies,
which is what `quick_reorder.py` permutes blindly.

The debugger route works and is the way to settle this per function. `c2.pdb` is published on Microsoft's symbol
server and `c2.dll` loads at its preferred base `0x10b00000` unrebased, so `cl.exe` can be run under the x86 `cdb`
with breakpoints taken straight from the PDB's public addresses - no symbol loading needed. Two practical notes:
one TU of ours costs ~1455 `GlobalRegAlloc` invocations and ~118k set-iterator calls, so breakpoints must be left
**disabled** (`bd`) and enabled only for the invocation of interest, and `gu` inside a breakpoint command makes
cdb skip the rest of that command. Identifying which invocation is the function you care about is the fiddly part:
hundreds of resolver-template instantiations allocate identically, so compile the file twice with the function
body emptied the second time and find the invocation whose iterator count drops by the difference.

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
