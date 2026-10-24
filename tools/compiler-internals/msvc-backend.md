# MSVC 14.00 backend notes (`c2.dll`)

Notes on the **compiler** rather than the game: what the bundled optimizer does, how it was read, and how to
observe it. The reimplementation-facing conclusions live in
[IMPLEMENTATION_CHEAT_SHEET.md](../../IMPLEMENTATION_CHEAT_SHEET.md); this file is the evidence behind them and
the starting point for digging further.

Everything here is about `MSVC1400-SP1/VC/bin/c2.dll`, `Microsoft (R) Optimizing Compiler Version
14.00.50727.762` - the toolchain this project builds with, so it is the authority on our codegen rather than a
proxy for it.

For a step-by-step walkthrough of the tooling aimed at a newcomer - what to measure, in what
order, and how to read each report - see [finding-mismatches.md](finding-mismatches.md).

## The spill-cost weight, read directly: it is `1 << loop_depth`

This supersedes the inferred chain in the two sections below, which was wrong at both ends. Read
out of the code rather than reasoned from the names, `Spillcosts` computes its own weight and
never consults the branch-prediction machinery.

### Where the weight comes from

`Spillcosts` opens `sub esp, 0x30` followed by four pushes, so the `[esp+0x28]` that it multiplies
by is a **local** at frame offset 0x18, not an incoming argument - the first thing that ruled out
the idea that a weight is handed in from elsewhere. It is written at five sites, all inside this
block:

```
0x10b1066a  cmp  dword ptr [_PogoFlag], 2
0x10b10671  jne  0x10b106d9                  ; no profile
            ; profile path: esi:edi = total count, [ebx+0x190] = this block's 64-bit count
            ;   total == 0            -> weight = 1
            ;   count <= 0            -> weight = 1
            ;   otherwise             -> weight = count * 0x2710 / total + 1
            ;                            (0x2710 = 10000, two 64-bit helper calls)
0x10b106d9  mov  cl, byte ptr [ebx + 0x17e]
0x10b106df  mov  eax, 1
0x10b106e4  shl  eax, cl                     ; weight = 1 << [ebx+0x17e]
0x10b106e6  mov  dword ptr [esp + 0x28], eax
```

So:

* **without a profile** - every build here - `weight = 1 << depth`, where depth is the `word` at
  `+0x17e` of the block record;
* **with `_PogoFlag == 2`** the weight is the block's share of the total execution count scaled by
  10000, plus one.

`+0x17e` is a **loop nesting depth**. Every write to it comes from loop machinery -
`@HoistOutOfLoop@16`, `@LpCanonicalizeLoops@4`, `@LgFindExitBlocks1@12`, `@LurNewBlock@12`,
`@FPHoistOutOfLoop@20` - and the block creators zero it or copy it from a parent:
`@FgSplitBlock@12`, `@FgInsertAirlockBlock@16`, `@PtInlDupInlineeBlock@8`, `@PogoOptNewBlock@4`.

### So the full key is

```
key(+0x0c) = sum over regions where the value IS referenced     ( refs * count * 2^depth )
           - sum over regions where it is live but UNREFERENCED (        count * 2^depth )
```

with `2^depth` replaced by the scaled profile share under PGO.

### The weight formula, verified by measurement

The `1 << depth` reading above was tested on `addUnitToSmallestBehaviourTypeTribe` rather than left
as a reading of the instructions, and it holds quantitatively.

**The spilled values are the lowest-keyed ones.** `reg_scores.py --find smallestSize` locates the
function at invocation #371 and gives its `+0x0c` keys:

```
aicIndex +87   slot +79   firstSlot +71   groupsCount +40   aiType +32
playerID +30   selectedTribeID +28   this +23   selectedSlot +14   smallestSize +2
```

`slot_map.py` independently reports exactly two values in stack slots - `_smallestSize$` and
`_selectedSlot$` - and those are precisely the two lowest keys, **+2** and **+14**. Two tools, one
reading the compiler's own records through a debugger and one inferring the frame from the
original's disassembly, agreeing without being fitted to each other.

**Removing one in-loop reference costs exactly one `count * weight` term.** Rewriting the loop
from a bound to a counter,

```cpp
for (int slot = firstSlot; slot < firstSlot + groupsCount; slot++)      // bound in the condition
for (int slot = firstSlot, remaining = groupsCount; remaining > 0; slot++, remaining--)
```

takes the `firstSlot + groupsCount` expression out of the loop condition, so `firstSlot` and `slot`
each lose one depth-1 reference. Measured:

| candidate | bound form | counter form | change |
| --- | --- | --- | --- |
| `firstSlot` | +71 | +57 | **-14** |
| `slot` | +79 | +65 | **-14** |
| `groupsCount` | +40 | +52 | +12 |
| `smallestSize` | +2 | -1 | -3 |
| `aicIndex`, `aiType`, `this` | +87, +32, +23 | unchanged | 0 |

Two independent values each lose **exactly 14** for losing one reference in the same loop - the
same `count * weight` term, as the formula requires - while every candidate the edit does not touch
moves not at all. `groupsCount` gains because the counter form gives it a new reference in the loop
initialiser.

**But the lever does not fix the function.** The point of the rewrite was that a counter is
referenced every iteration where a bound merely lives across the body, so its key should rise
enough to win a register and drop the frame from 12 to the original's 8. It does not: the frame
stays at `+4`, and the instruction mix gets much worse - delta 10 to 22, `kind` 0.893 to 0.846,
quick_diff 0.6803 to 0.6179 - because the counter form emits a decrement the original does not
have. The original keeps a genuine bound in `edx`; the counter shape is simply not what it
compiled.

So the formula is now verified and usable for *predicting* which value is at risk of spilling, and
the measurement confirms the mechanism. What it does not provide is a way to rescue a particular
value here: the only moves available change the instruction stream more than they change the
ranking. Treat it as a diagnostic - "this value will spill because its key is lowest, and here is
the term responsible" - rather than as a fix.

### What the Bp heuristics actually feed

Not this. `@BpBlockProbabilities@4` has exactly one caller,
`@BpComputeFlowgraphProbabilities@4`, and that has exactly two:
`@PtInlFindInitialPartialInlineeAux@12` and `@PtInlComputeBenefit@4`. `@FgWeightFlowGraph@4`'s
five callers are `@DoInline@24`, `@PtInlCollectBUInfo@12`, `@LiListFunction@4`,
`@X87MapGFxToSTx@4` and `@PogoFgCreateScaledZeroCounts@20`.

The static branch-prediction suite is an **inliner** input - it estimates how much a partial
inline is worth - plus an x87 mapping use and a profile path. It does not reach register
allocation, and `Spillcosts` does not call any of it.

That is the whole reason the guard-inversion test came out flat: inverting
`if (aiType == AITA_NULL) return 0;` changes which arm is predicted taken, but it does not change
any block's **loop depth**, so no weight moves, so no key moves, so the allocation is untouched -
which is exactly what was measured, with the register substitution profile identical in kind and
count. It also explains, in passing, why `#pragma inline_depth(1)` perturbed codegen in the
earlier pragma sweeps while the branch-shape rewrites did not: inlining is the consumer of that
chain.

### The lever this does give

Loop depth, and it is predictive. A reference inside a loop at depth *d* contributes `2^d` to its
value's key; the same reference outside contributes 1. A value that is live across a loop without
being referenced in it is charged `2^d` per such region. So moving a reference into or out of a
loop changes that value's allocation priority by a factor of two per level, in a direction the
formula states in advance - which is a much sharper instrument than the branch-shape rewrites
tried above, and the one to reach for when a value is enregistered on one side and spilled on the
other.

Worth noting what this predicts about the functions in this file: `playerID` in
`aiGiveRaidInstructions` keys at **-147** because it is live across a depth-1 loop while being
referenced almost entirely outside it, so it collects the `count * 2` penalty repeatedly - and
`slot_map.py` independently shows it in a stack slot. The model and the observation agree without
being fitted to each other.

## Superseded: static branch prediction feeds register allocation (it does not)

`Spillcosts` keys on `refs * count * weight`, and `weight` is a block frequency. Following where
that comes from leads to the one lever found so far that the source actually controls.

Block weights come from `@FgWeightFlowGraph@4` / `@FgWeightGraph@12`, which consume edge
probabilities from `@BpBlockProbabilities@4`. With a profile loaded that is
`@BpComputeFlowgraphPogoProbabilities@4`; without one it is `@BpComputeFlowgraphProbabilities@4`,
which combines a suite of static heuristics - the classic Ball-Larus set, each one named:

```
@BpLoopBranchHeuristic@12   @BpReturnHeuristic@12     @BpCallHeuristic@12
@BpPointerHeuristic@12      @BpOpcodeHeuristic@12     @BpGuardHeuristic@12
@BpLoopExitHeuristic@12     @BpLoopHeaderHeuristic@12 @BpCmpHeuristicTemplate@8
```

So the chain is

```
branch shape -> Bp*Heuristic -> BpBlockProbabilities -> FgWeightFlowGraph -> block weight
             -> Spillcosts key -> InsertInList order -> ChoosePhysReg
```

and **which arm of a branch you write first can change the register allocation**.

### Two of them decoded

Each heuristic returns three values - `-1`, `0` or `+1` - built with the `sbb eax, eax` and
`lea ecx, [ecx + ecx - 1]` idioms, where `-1` means "this heuristic does not apply".

`BpReturnHeuristic` at `0x10c72f00` walks each successor to its terminating instruction, chasing
up to five links through `+0xc`, and tests the tuple opcode at `+8` against **`0x10` and `0x19`**,
the two return forms:

* both successors return, or neither does - `cmp esi, eax; jne` falls through to
  `or eax, 0xffffffff` - the heuristic **abstains**
* exactly one returns - the **non-returning** arm is predicted taken

`BpCallHeuristic` at `0x10c73030` is the same shape against opcode **`0x0f`**, a call: scan each
successor's instruction list, and if exactly one arm contains a call, the arm **without** the call
is predicted taken. (The opcode numbers are inferred from the function names plus the surrounding
code, not from a typed enum; the control flow is read directly.)

### Why this is the useful one

It is predictive rather than trial-and-error. A branch only has its probability - and therefore
its block weight, and therefore its contribution to every candidate's spill cost - decided by arm
order **when the heuristic discriminates**, which is when exactly one arm returns or exactly one
arm calls. Otherwise the heuristic abstains and arm order is free.

That retro-explains both results this file already records, which is the reason to trust it:

* `aiGiveRaidInstructions` gained **56.8% -> 60.3%** from swapping the arms of its final
  `if`/`else`. Swapping changed which arm is the fallthrough, and with it the predicted
  probabilities feeding the weights.
* `playNervous2BikFromPlayer` was **byte-identical** across four source forms, including
  early-return against guarded-call. Under this model that is expected: both forms leave both
  arms reaching a return, so `BpReturnHeuristic` abstains either way and nothing downstream
  moves.

### How to use it

When a function is structurally correct but its registers or frame differ, look for branches where
exactly one arm returns or exactly one arm calls, and check our arm order against the original's.
`structural_diff.py` already reports polarity flips; this says which of them are worth acting on -
a flip on a branch where the heuristics abstain is cosmetic, a flip on a discriminating branch
moves the block weights and can move the allocation.

Still unread, in rough order of likely value: `@BpGuardHeuristic@12` (guard clauses, which the AI
code is full of), `@BpLoopExitHeuristic@12` and `@BpLoopBranchHeuristic@12` (the loop-carried
values that several of these functions spill), and `@BpOpcodeHeuristic@12` with
`@BpCmpHeuristicTemplate@8`, which would say whether the *comparison operator* itself shifts a
probability - that would make `!= 0` against `> 0` a codegen-relevant choice rather than a
stylistic one.

### Correction: tested, and it is not a usable lever

The section above was written before the lever was tested. Two things it claimed are wrong, and
the practical conclusion does not survive.

**`BpGuardHeuristic` is inert.** Decoding `0x10c72e70` shows every path, including the one that
reaches the computation at `0x10c72edb`, falling through to

```
0x10c72eec  or   eax, 0xffffffff
0x10c72ef1  ret  4
```

`or eax, -1` discards whatever was computed, so the function **always returns -1**, which is the
abstain value. The guard heuristic never contributes in this build - the opposite of the
prediction above that it would be the most valuable one to read next. Whether that is deliberate
neutering or a discarded result, the behaviour is the same.

**The retro-explanation of `aiGiveRaidInstructions` was wrong.** Its winning branch is
`if (canNavigate(...)) commandUnitsToLocation(...) else sendUnitsToCampfire(...)`. Both arms
contain a call, so `BpCallHeuristic` abstains; neither arm returns, so `BpReturnHeuristic`
abstains. Both heuristics abstain on the one branch whose arm order was worth 3.5 points, so that
gain was plain instruction ordering and had nothing to do with block weights. Fitting it to this
model was wishful.

**The direct test shows no effect on allocation.** `addUnitToSmallestBehaviourTypeTribe` opens
with `if (aiType == AITA_NULL) return 0;` followed by the body - a branch where
`BpReturnHeuristic` genuinely discriminates, one arm being a return block and the other the rest
of the function. Rewriting it as `if (aiType != AITA_NULL) { body } return 0;` is semantically
identical and flips which arm the heuristic predicts taken. Measured:

| | instructions | `kind` | mix delta | quick_diff | frame | register substitutions |
| --- | --- | --- | --- | --- | --- | --- |
| baseline | 122 | 0.893 | 10 | 0.6803 | +4 | 27 |
| inverted guard | 123 | 0.849 | 11 | 0.5878 | +4 | 29 |

The code changed - one extra jump and a different block layout - but the **register allocation did
not move at all**. The substitution profile is identical in kind and count: `eax -> edi` 8 times,
`ecx -> edi` 5, `edi -> edx` 4, `eax -> edx` 3, `edi -> ecx` 1, `ebp -> edi` 1 in both, with the
totals differing only by the two added instructions. The frame stayed at `+4`.

So what survives is only what was read directly off the code: the call chain from the `Bp*`
heuristics through `BpBlockProbabilities` and `FgWeightFlowGraph` into the weight that
`Spillcosts` multiplies, and the decoded behaviour of `BpReturnHeuristic` and `BpCallHeuristic`.
What does **not** survive is the claim that this gives the source a handle on allocation. On the
one function where the construction could be made cleanly, flipping a discriminating branch moved
the block structure and left every register where it was.

Possible reasons, none of them established: the weight change may be too small to reorder any
candidate given the margins seen in the `+0x0c` keys (`tile` 212 against the next at 148); the two
source forms may present the same successor shapes to the heuristic despite looking different;
or the probability-to-weight step may compress differences more than the chain suggests. Settling
it would mean reading `FgWeightFlowGraph` and `BpBlockProbabilities` rather than inferring from
the ends of the chain, and measuring the weights directly under the debugger the way `Spillcosts`
was measured - which is the next thing to do before anyone trusts this path again.

## The PGO flag: three gated behaviours, and the phase order

The global at `0x10d0ffdc` that an earlier section could only describe as "a mode flag, read in
about 400 places, set at invocation level" is **`_PogoFlag`**, the per-function copy of
**`_PogoMasterFlag`** at `0x10d44b4c`. Pogo is Microsoft's internal name for PGO, and the flag
gates three separate behaviours that between them cover both the allocation and the scheduling
walls this file keeps running into:

| value | what changes |
| --- | --- |
| 0 (our builds) | full tail merging; `Spillcosts` penalty is `count * weight` |
| 1 (instrument) | `FgTryTailMerge` returns immediately - **no tail merging at all** |
| 2 (optimise) | `Spillcosts` penalty is just `weight`; `PogoOptCodeMotion` runs as an extra pass |

`FgTryTailMerge` at `0x10b2e1b0` opens with `if (_PogoFlag != 1)` wrapping its entire body, which
makes sense - merging blocks would corrupt the profile counters being collected. That is the pass
that merges the duplicate `aiGiveRaidInstructions` is missing.

**The phase order**, from the twelve `dop2_*` entry points in address order:

```
GetInitialTuples -> InitialOptsAndSetup -> PreLowerGlobalOpts -> Codegen ->
PostLowerPreRegAllocGlobalOpts -> GlobalRegAlloc -> CodegenUpdate ->
PostCodegenFlowOpts -> CodegenFinish -> FinalFlowOpts -> PreEncode -> EncodeAndRelated
```

`GlobalRegAlloc` is phase 6 and `FinalFlowOpts` is phase 10, and `dop2_FinalFlowOpts` is where
`FgDoLateFlowOpts`, `FgCodeMotion` and - only when `_PogoFlag == 2` - `PogoOptCodeMotion` are
called. So **tail merging and code motion run after register allocation**, which independently
confirms the claim made earlier in this file: two arms whose instructions are identical except
for their registers are not mergeable, so the allocation can be what preserves a duplicate.
`FgCodeMotion` is also the pass that sinks a load past a branch, which is what no source form of
`playNervous2BikFromPlayer` could prevent.

### Forcing the flag: a real lever, but not the explanation

`pogo_probe.py` compiles one file twice, the second time with `_PogoFlag` forced across
`Spillcosts` only - an entry breakpoint sets it and the `ret` at `0x10b1153f` restores it - so the
allocation penalty changes while the profile-dependent passes never see a value the build was not
configured for. It does change allocation, measurably, on
`addUnitToSmallestBehaviourTypeTribe`:

| | frame | distinct callee-saved | instructions | `kind` vs original | mix delta |
| --- | --- | --- | --- | --- | --- |
| original | **8** | **4** | **122** | - | - |
| baseline | 12 | 3 | 122 | **0.893** | **10** |
| `_PogoFlag=2` | **8** | **4** | 115 | 0.624 | 15 |

The smaller penalty does exactly what the formula predicts - the frame drops from 12 to the
original's 8 and one more value is enregistered, which is the direction every register-pressure
difference in this namespace pointed. But the overall match gets **worse**, because other `== 2`
paths activate and strip seven instructions. On `aiGiveRaidInstructions` it moves the two
contested values from `ebx`/`ebp` - the original's pair, merely swapped - to `esi`/`edi`, which is
further away.

So the spill-penalty term is a confirmed lever on allocation and on frame size, and it is not the
explanation for the gap; the original was not simply built in this mode. It is worth re-testing
per function when a frame comes out too large, since that is the one symptom it reliably fixes.

A warning from getting this wrong once: the first attempt put the restore breakpoint on the last
*byte* of `Spillcosts` rather than on its `ret`, so it never fired, the flag stayed 2 into the
profile-dependent passes, and the compile died on a null dereference in `FgFindDominatorsGraph`.
Bracket on a real instruction address, and keep a second restore at the next phase entry.

### Reading the symbol table without Ghidra

`pdbnames.py` recovers 9687 public symbols from `c2.pdb` by scanning for `S_PUB32` records
(`u16 reclen | u16 0x110e | u32 flags | u32 offset | u16 segment | name`) and mapping
segment-plus-offset through the PE section table. It is the practical name-to-address route,
because ghidra-mcp's name searches ignore the `program` argument and query whatever program is
current, while only `get_function_by_address` honours it. PDB names are decorated
(`@Spillcosts@12`) where Ghidra shows them stripped; every address agrees.

Pass names worth knowing, all from that map:

| area | symbols |
| --- | --- |
| tail merge / cross jump | `@FgTryTailMerge@16`, `@FgDoCommonTailMerge@20`, `@FgTailMergeWithoutCheck@8`, `@FgCrossJumpRemove@4`, `@PpSsaMdSubstPreventsTailMerge@8` |
| code motion and sinking | `@FgCodeMotion@4`, `@FgChangeSink@12`, `@GoptInvariantCodeMotion@12`, `@GoptCodeMotionBlock@12` |
| scheduling | `@Schedule@8`, `@SchNeedSchedule@8`, `@SchSchedGraph@4`, `@SchmdBlockNeedPreSchedule@8`, `_preSched` |
| profile-driven | `@PogoOptCodeMotion@*`, `@PogoCreateFinalOrder@4`, `@PogoDecorateFG@4`, `@BpComputeFlowgraphPogoProbabilities@4` |

`SchNeedSchedule` turns out to be a weak lever - it schedules any block with more than one real
instruction, gated only on `_preSched` for the pre-pass - but `@PogoCreateFinalOrder@4` shows that
final block order is profile-driven in PGO builds, which is a scheduling difference no source
change can reach.

## The resolver switches change the score but not the code

Both resolver switches are **off** in a fresh checkout - 829 `MACRO_STRUCT_RESOLVER(..., false, ...)`
in `src/OpenSHC/Globals` and every `MACRO_FUNCTION_RESOLVER` in the `.func.hpp` files - and every
measurement in this file was taken that way until it was checked. Turning both on
(`tools/reimplementation-control/enable_reimplemented_data.py` and
`tools/reimplementation-helper/batch/enable_local_functions.py`) moves the reccmp percentage a long
way:

| function | resolvers off | resolvers on |
| --- | --- | --- |
| `computeAttackPossibilities` | 72.4 | **89.7** |
| `recruitHarrassingSiegeEngines` | 65.9 | **73.2** |
| `playNervous2BikFromPlayer` | 64.0 | **76.0** |
| `decideOnTribeAttackLocation` | 64.4 | **68.8** |
| `renderDebugDataAiInfo` | 95.4 | **99.0** |
| `updateAIPlayerState` | 78.6 | **81.7** |
| `aiShouldAttackOrWaitForTeamCoordination` | 80.2 | **83.2** |
| `aiRecruitUnits` | 48.0 | **50.0** |

The whole build list averages **94.20 over 60** functions with them on. So any percentage quoted
from a default checkout is understated, sometimes by seventeen points, and a figure is only
comparable to another taken in the same configuration.

**But the structural measures do not move at all.** With the resolvers on, `slot_map.py`,
`structural_diff.py` and `quick_diff.py` return byte-identical results -
`addUnitToSmallestBehaviourTypeTribe` still reports frame `+4`, `kind` 0.893 and mix delta 10, and
the quick_diff ratios stay at 0.8000, 0.6803 and 0.7284 to four decimals. The reason is that a
resolver changes an *operand*, not an instruction: `mov ecx, OFFSET ?instance@...StructResolver@@`
against `mov ecx, 0x2157578` is the same `mov`, and a call through a trampoline is still one
`call`. reccmp scores operands, so it sees the difference; a mnemonic-level or frame-level
comparison does not.

That is a useful division of labour rather than a problem. The structural tools can be run in a
default checkout and trusted, and the resolvers only need flipping when a percentage is about to be
recorded. It also means the conclusions this file draws about frames, instruction mix and register
pressure are unaffected by the switch - they were checked.

### /GL does not transfer to this namespace

`enable_local_functions.py` documents the reason the function resolvers matter beyond runtime:
`/GL` buys nothing while a call still leaves the module, because LTCG cannot see the callee's
register use, and flipping `getSellResourceAmount` took `getSalesPrice` from 68.4% to 100% because
the original keeps `this` in the volatile `edx` across that call. That is exactly the symptom class
behind every register-pressure wall in this file, and no AICState file had ever been given `/GL` -
`cmake/compiler-flags-gl.txt` had 22 entries, none of them AICState.

Adding all sixty, with the function resolvers on, and verifying `/GL` really reached the compile
command (120 of 120 AICState entries carry it; `file_dependent_read_list` in `CMakeLists.txt`
makes cmake reconfigure when that list changes) produced **no gain whatsoever** - every function
identical, and `planToBuyWhenLowOnResourceAndSnoozeBuildings` 0.8 worse.

The likely reason is visible in the call sites: AICState's hot callees -
`checkTribeActivityPercentages`, `selectRandomBuildingIDFromListOfBuildingTypes`, and the
`TribesState`/`UnitsState` methods - are not in the build list at all, so those calls leave the
module whatever the flags say. `getSalesPrice` won because its callee was in the list beside it.
So the lever is real but its precondition is unmet here, and the concrete next step is to bring
those callees into the build list first and only then retest `/GL`.

## Every decoded name, confirmed against c2.pdb

The whole backend model in this file was decoded from unnamed code, so it is worth recording
that it has since been checked against the real symbols. Loading `c2.dll` **with its PDB** into
a Ghidra project confirms every function this file names, and resolves the one naming confusion
it had:

| address | PDB name | what this file decoded it as |
| --- | --- | --- |
| `0x10c07350` | `dop2_GlobalRegAlloc` | the register-allocation driver |
| `0x10b10420` | **`Spillcosts`** | accumulates the `+0x0c` ordering key |
| `0x10b11970` | `InsertInList` | candidate priority list, sorts on `+0x0c` |
| `0x10b119f0` | **`InsertByBenefit`** | the other insert, sorts on `+0x40` |
| `0x10b14b70` | `ChoosePhysReg` | picks the cheapest free register |
| `0x10beaef0` | `ColorStackElements` | the stack-slot colourer |
| `0x10beb760` | `colorElemental` | per-element slot placement |
| `0x10beb730` | **`StkGSBufferLevel`** | the class byte at `+0x18` |

Three of those are worth dwelling on.

**`Spillcosts`** is the function whose tail accumulates `+0x0c`, and the name is the semantic:
the key is a spill cost. A value gains `refs * count * weight` in each region where it is
referenced and is charged `count * weight` for each region it is live across without being
referenced - which is exactly what "what would it cost to spill this" means. The formula was
derived from the arithmetic before the name was known, and they agree.

**`InsertInList` against `InsertByBenefit`** explains the error this file used to contain. The
two are adjacent and nearly identical; the old note said "InsertInList sorts on `+0x40`, the
benefit" when in fact `InsertInList` sorts on `+0x0c` and it is `InsertByBenefit`, 0x80 bytes
later, that sorts on `+0x40`. The names make the distinction explicit, and the candidate list
the harness breakpoints is the former.

**`StkGSBufferLevel`** settles the class byte outright. The `/GS` reading in the section above
was an inference from the arithmetic plus one observed layout; the name says it directly - `Stk`
for stack, `GS` for the buffer security check, `BufferLevel` for the classification. Its
decompilation is also identical to the hand-decode, including `sym+0x63 < 3` for `<= 2`:

```c
char StkGSBufferLevel(sym)            /* sym in EAX */
{
  if (((sym+0x37 & 0x40000) != 0) && (sym+0x63 < 3) && (4 < sym+0x1c))
    return 3;
  return ((sym+0x20 & 0x4000000) != 0) + 1;
}
```

The PDB does **not** apply struct types, so the operands are still raw offsets and the fields of
the symbol record remain unnamed. The function names are what the PDB buys.

**How to query it.** `ghidra-mcp`'s read tools take a `program` argument, so a non-current
program can be queried without disturbing anything:

    get_function_by_address(address="0x10beb730", program="c2.dll")

That matters because `switch_program` reports success but does **not** redirect the query tools -
after switching, `get_metadata` still named the game executable and symbol lookups still missed.
Pass `program` instead of switching, and a shared session's `currentProgram` is never touched.
REA remains the alternative when no PDB is wanted, but it refuses a caller-supplied PDB
companion, which is why it could only ever report `FUN_` names.

## Getting symbols

`c2.dll` references `c2.pdb`, and Microsoft still publishes it:

```
https://msdl.microsoft.com/download/symbols/c2.pdb/8E3C6AD714BE4E55B528B0DBEB3BABD81/c2.pdb
```

(947 KB; the path is `<name>/<GUID><age>/<name>` from the RSDS record in the debug directory.) It is a
publics-only PDB - no line numbers, no locals, no struct layouts - but it names every function, and mangled C++
names carry parameter types for free, e.g.
`?ProcessFunc@CControlGraph@OptDbgNameSpace@@QAEXPAUILivenessCallback@2@@Z`.

Tools that will not accept a caller-supplied PDB can still be used: parse the `S_PUB32` records out of the PDB
(`reclen, rectyp=0x110E, flags, off, seg, name`), map `(seg, off)` through the PE section table, and you have a
name-to-address table to drive an address-based disassembler or a debugger. `c2.dll`'s image base is
`0x10b00000`.

The retail build has **no** internal dump switch - no `-d2*` option strings, no asserts, no trace output. The only
diagnostic strings are the PGO log (`Trace formation`, `Copy Elim`, `HCO Def Push`, `PEEP:`). There is no free
ground truth; it has to be read or traced.

## The backend's own source layout

The fatal-assert path passes `__FILE__`, so the binary leaks 66 source paths. Useful ones:

| area | file |
|---|---|
| stack slot layout | `P2/stack.c` |
| coloring | `P2/color.c` |
| register assignment | `P2/regasg.c` |
| global optimizer | `P2/globopt.c`, `P2/globlopt.c`, `P2/globdf.c` |
| IR | `P2/tuple.c`, `P2/fg.c`, `P2/dag.c` |
| x86 lowering and emission | `P2/x86/lower.c`, `P2/x86/code.c`, `P2/x86/mdlist.c`, `P2/x86/fpreg.c`, `P2/x86/fpo.c` |

An assert also gives a file *and line*, which anchors a function to its source: `ColorStackElements` reports
`P2/stack.c` line 1372.

## Addresses

VAs for an unrebased load at `0x10b00000`:

| symbol | VA |
|---|---|
| `@dop2_GlobalRegAlloc@4` | `0x10c07350` |
| `@dop2_PostLowerPreRegAllocGlobalOpts@4` | `0x10c07350`-adjacent, see PDB |
| `@Color@4` | `0x10b0cf40` |
| `@SsaColor@4` | `0x10be2b30` |
| `@CanColorPseudoreg@12` | `0x10b1b920` |
| `@ColorStackElements@12` | `0x10beaef0` |
| `@StkColorCmp@12` | `0x10bebb30` |
| `@QSortColors@12` | `0x10bebbb0` |
| `@SwapColors@8` | `0x10bebcf0` |
| `@StkColorWeightForEBPAdj@12` | `0x10bec120` |
| `@StkInsertDummyColor@8` | `0x10bec3c0` |
| `@Spillcosts@12` | `0x10b10420` |
| `@SpillOrDefer@12` | `0x10b0d690` |
| `@RegSpill@12` | `0x10bdad70` |
| `@CgAnnotateEdgeWeight@12` | `0x10b061d0` |
| generic bitset iterator (`FUN_10b04fa0`) | `0x10b04fa0` |

## Stack slot assignment - decoded

`ColorStackElements` builds one 28-byte record per stack element, sorts the records with `StkColorCmp`, and hands
out offsets in the sorted order. Record fields in use: `+0x08` the local's size rounded up to 4, `+0x0C` its
accumulated reference weight (accumulated with `+=` when elements merge), `+0x18` a class byte.

```c
// StkColorCmp
if (a->class != b->class)                  // byte at +0x18, unsigned
    return (a->class > b->class) ? (dir ? +1 : -1) : (dir ? -1 : +1);
ka = (a->weight * 1000) / a->size;         // +0x0C scaled, divided by +0x08
kb = (b->weight * 1000) / b->size;
return ka == kb ? 0 : (ka >= kb ? +1 : -1);
```

So for a homogeneous block of same-class scalars the layout is **descending weight per byte**. The direction flag
is a function-level property; `ColorStackElements` walks the sorted elements `0..n` or `n-1..0` accordingly and
passes the same flag to `QSortColors`.

Confirmed on `planToBuyWhenLowOnResourceAndSnoozeBuildings` (fourteen `int allowX = 1;` locals, eleven colored):

| slot | local | refs | declared |
|---|---|---|---|
| -48 | allowBlacksmiths | 5 | 6th |
| -44 | allowTanners | 5 | 7th |
| -40 | allowQuarries | 4 | 8th |
| -36 | allowWoodcutters | 4 | **4th** |
| -32 | allowBakeries | 4 | 9th |
| -28 | allowBreweries | 4 | 10th |
| -24 | allowInns | 4 | 11th |
| -20 | allowWells | 3 | 13th |
| -16 | allowFarms | 3 | **12th** |
| -8 | allowIronMines | 3 | **1st** |
| +8 | allowArmourers | 5 | 1st, on `_playerID$`'s slot |

Monotone in weight, scrambled in declaration order. Two further checks: adding **one** reference to a local
reshuffled the whole table - another local left the stack for a register, a third took a vacated slot - and the
result was again exactly monotone (`5 5 5 4 4 4 4 3 3 3`); and renaming `allowQuarries` to `zzz` and
`allowWoodcutters` to `aaaaaaaaaa`, inverting both alphabetical order and length for an adjacent equal-weight
pair, left the function byte-identical.

The **class byte at `+0x18`** is the primary key, and it is no longer unknown. A twelve-instruction
classifier at `0x10beb730` computes it, and the placement pass at `0x10beb760` inlines the same thing:

```
0x10beb730  test dword ptr [eax + 0x37], 0x40000
0x10beb737  je   0x10beb748
0x10beb739  cmp  dword ptr [eax + 0x63], 2
0x10beb73d  jg   0x10beb748
0x10beb73f  cmp  dword ptr [eax + 0x1c], 4
0x10beb743  jle  0x10beb748
0x10beb745  mov  al, 3
0x10beb747  ret
0x10beb748  test dword ptr [eax + 0x20], 0x4000000
0x10beb74f  setne al
0x10beb752  add  al, 1
0x10beb754  ret
```

that is

```
class(symbol) = 3                                      when (symbol+0x37 & 0x40000)
                                                        and symbol+0x63 <= 2
                                                        and symbol+0x1c  >  4
              = 1 + ((symbol+0x20 & 0x4000000) != 0)   otherwise
```

so the class is **1, 2 or 3**, and the only size-dependent term is `symbol+0x1c > 4`: anything wider
than a dword takes class 3 and sorts as a group apart from the scalars. The byte is written only when
a gate holds -

```
((flags(DAT_10d195cc + 0x44c) & 0x20000) && DAT_10d0d700[0x17]) || (byte(DAT_10d0d700 + 0x2b) & 1)
```

- and otherwise stays 0, so with that feature off every slot shares one class and the key degenerates
to the weight alone.

**What it is.** Read off the arithmetic rather than from a symbol name, this is the `/GS`
buffer-ordering rule: arrays are what can overflow, so they are classed separately and placed nearest
the canary. `renderDebugDataAiInfo` corroborates it - `char text[1000]` sits at `-1004`, above every
int scalar (`-1024` through `-1008`) and immediately below `__$ArrayPad$` at `-4`, which is the layout
that rule produces. The `/GS` reading is an inference from the arithmetic plus that one observation,
not a proven name; the arithmetic itself is read directly off the instructions.

That explains the symptom this entry used to record as unexplained - arrays and address-taken locals
interleaving with scalars for reasons the weight model does not cover - because the class outranks the
weight.

**It does not unblock `planToBuyWhenLowOnResourceAndSnoozeBuildings`**, which is what prompted the
work, and the prediction that it would was wrong. All ten of that function's locals are `int`, so
`symbol+0x1c` is 4 for each, none reaches class 3, and the class is uniform unless the `0x4000000`
flag differs between them. That leaves the weight, where both sides agree, and then declaration
order, which a hill-climb over all fourteen declarations plus three hand-made swaps showed is already
a local optimum. The byte discriminates by width, and that function has nothing but dwords.

Finding this file's functions, since it is not obvious: the four `P2/stack.c` assert sites come from
searching the image for the UTF-16 path and then for pushes of its address. Their line numbers are
1372, 2533, 2534 and 2573, and 1372 is the one already attributed to `ColorStackElements`, which
fixes that function at `0x10beaef0`.

`slot_weight.py` in `../reimplementation-helper/batch/` reports this per function.

## Registers - what is and is not known

**Established.** `.rdata` holds the register names in three parallel 4-byte-stride tables terminated by
`"noreg"`. The table is indexed **backwards from its end**, and the numbering is 1-based in x86 encoding order:

```
eax=1  ecx=2  edx=3  ebx=4  esp=5  ebp=6  esi=7  edi=8      (0 = none)
```

An earlier revision of this file read the table forwards and recorded the reverse (`edi=0 ... eax=7`). That was
wrong; reading `0x10cfc190 - (n-1)*4` reproduces the names above exactly.

**Established.** A set is a 64-bit bitvector with set/clear mask tables indexed by `n & 0x3f`
(`DAT_10cf65e8`/`DAT_10cf67e8`), and the iterator at `0x10b04fa0` takes the lowest set bit, adds the set's base,
and clears the bit - so a set is always walked in ascending order:

```c
for (; (set >> bit & 1) == 0; bit++) {}   // low dword first, then the high one
return set_base + bit + dword_offset;
```

**Not established.** That iterator is *generic*, not a register allocator. Where its use could be observed it was
walking sets of symbols - `ColorStackElements` feeds its result straight into a symbol array as
`DAT_10d0faa4 + n * 4` - and tracing `sellExcessGoods`'s allocation returned members numbered 0 to 40 across 140
distinct set objects, which is a symbol or pseudo-register space rather than the eight GPRs. An earlier claim here
that register choice is "the lowest-numbered free register" was an inference from the name table plus the
ascending-order mechanic, and is retracted.

`Spillcosts` is 854 lines of live-set bitvector manipulation with no cost arithmetic in it, which suggests the
cost model decides *who gets spilled* rather than *which register a winner gets*, but that is also not traced.

### Where registers are actually chosen

Tracing one function's allocation answered this. During `sellExcessGoods` (invocation #613) the colouring entry
points ran as follows - `Color` once, `SsaColor` twice, `ColorStackElements` once, `Spillcosts` six times,
`SpillOrDefer` seven times, and `CanColorPseudoreg` and `RegSpill` not at all. So `@Color@4` is the per-function
register colourer, and bounding it with the next public symbol gives its 29 direct callees, among them:

| callee | VA |
|---|---|
| `@ChoosePhysReg@12` | `0x10b14b70` |
| `@OrderGlobregs@12` | `0x10b11770` |
| `@SubsumeGlobregs@8` | `0x10b0fdb0` |
| `@InsertNewGlobregs@8` | `0x10b133e0` |
| `@UpdateAffectedGlobregs@20` | `0x10b15470` |
| `@HandleCurrUncolorable@8` | `0x10b0d830` |
| `@BetterToDefer@4` | `0x10b19de0` |
| `@InitialSplitPoints@16`, `@InsertSplitPoints@28` | `0x10b0ded0`, `0x10b13460` |

**`@ChoosePhysReg@12` is where a physical register is picked.** Its second argument (`edx`, it is `__fastcall`)
is the **mask of still-available registers**, and watching that mask across calls gives the consumption order
directly. During `sellExcessGoods` it ran 18 times and the mask walked:

```
ffffffff -> fffffffd -> ffffffed -> fffffeed -> fffffeec -> fffffee8
            bit 1       +bit 4      +bit 8      +bit 0      +bit 2
            esi         ebx         (non-GPR)   edi         ebp
```

which is exactly our generated prologue, `push esi; push ebx; push ebp; push edi`. The original consumes the same
four registers in the opposite order, `ebp -> edi -> ebx -> esi`. That difference is now an **observable**, not an
inference: run the trace, read the mask progression, compare with the original's prologue.

`eax` is not the chosen register - it returns pointers or 0 - so the assignment is recorded in a structure rather
than returned.

Internally `ChoosePhysReg` does use `bsf` (lowest set bit) over a mask, at `0x10b14d03` and `0x10b151de`, and the
mask is first narrowed with the same 64-bit set/clear tables (`and`/`or` against `DAT_10cf65e8`/`DAT_10cf67e8`).
So "lowest-numbered free register" holds **within the already-filtered candidate set**, which is why the observed
consumption order (1, 4, 0, 2) is not ascending.

### Which candidate asks first: OrderGlobregs and InsertInList

`@OrderGlobregs@12` (`0x10b11770`, 512 bytes) runs once per function and does **not** sort - it builds an ordered
list by repeated insertion through `@InsertInList@8` (`0x10b11970`), which is 128 bytes and fully readable. In it
`eax` is the candidate being inserted and `edi` the list head, `+0x14`/`+0x18` are next/prev, and there are two
sort keys:

```c
// InsertInList - list kept in descending (key, key2) order
if (new->key  >  p->key)                    insert new before p;   // +0x0c, compared SIGNED
else if (new->key == p->key &&
         new->key2 >= p->key2)              insert new before p;   // +0x44, compared UNSIGNED
else                                        advance to p->next;
```

with an insert-at-front fast path when the new node outranks the head, so among equal keys the newer candidate
goes first. `+0x44` is a small symbol id used only as a tiebreak.

`+0x0c` is **not** the benefit, though an earlier reading of these notes said so. The sibling inserter
`@InsertByBenefit@8` (`0x10b119f0`) orders on `+0x40` and *copies* `+0x0c` from the list neighbour
(`mov ecx,[ecx+0xc]; mov [edx+0xc],ecx`), and `@BetterToDefer@4` sets `+0x0c` to `min(components) - 1`, so
`+0x0c` is a rank derived while ordering. The benefit is **`+0x40`**, which `BetterToDefer` also gates on
(`cmp dword ptr [eax+0x40], 0; jle` - not worth it). Tracing all three fields for `sellExcessGoods`:

| name | `+0x0c` rank | `+0x40` benefit | `+0x44` id |
|---|---|---|---|
| `amount` | +104 | **70** | 111 |
| `variance` | -4 | **22** | 110 |
| `resourceType` | -34 | **20** | 39 |
| `j` | +88 | **20** | 108 |
| `resourceOffset` | -26 | **20** | 35 |
| `playerResourceBase` | -52 | **12** | 17 |
| `aicIndex` | +88 | **8** | 20 |
| `this` / `aiType` | -134 / +42 | **6** | 8 / 4 |
| `playerID` | -134 | **4** | 7 |

The benefit is a small positive **weighted use count**: `amount`, assigned in eight branches and read by the
`sellGoods` call, scores 70; `playerID` scores 4. So register candidacy is driven by the same quantity as stack
slot order - how often, and at what loop depth, a value is used.

Traced over `sellExcessGoods`, the candidates and their scores look like this (40+ insertions, abbreviated):

```
key=+104 key2=6f    key=+97 key2=11    key=+96 key2=22    key=+88 key2=14
key= +88 key2=6c    key=+85 key2=74    key=+72 key2=6b    key=+64 key2=27
key= +42 key2=04    key=+40 key2=0b    key=+32 key2=08    key=+32 key2=07 ...
key=  -4 key2=6e    key=-20            key=-26 key2=23    key=-34 key2=27 ...
key=-155             key=-156           key=-160
```

So the pass scores every candidate and orders them by descending benefit; the positive-scoring ones are the
handful that actually win registers, and they ask `ChoosePhysReg` in that order. Candidates recur with different
scores across the run (`key2=0x27` appears at -34, then +64, then -2), which is the colourer iterating - `Color`
runs once but `Spillcosts` and `SpillOrDefer` run six and seven times for this function, re-scoring between
rounds.

**The whole chain, then:** `OrderGlobregs` scores and orders the candidates, `Color` walks that order, and
`ChoosePhysReg` serves each from the still-available mask. Since the order is a benefit score derived from how
values are used, the source-level lever on register assignment is the same one as for stack slots - how often and
where each value is read - which is why permuting statements sometimes moves a register and usually does not.

### Reading the scores per source variable

The candidates *can* be mapped back to source names. A candidate node's `+0x00` is its symbol record (0 for a
compiler temporary), the symbol record's `+0x04` points one byte before the variable's name, and the names sit in
a string pool with a small header packed after each string:

```
name = poi(poi(poi(candidate) + 4)) + 1
```

`reg_scores.py` does this. `--probe` counts candidate insertions per `GlobalRegAlloc` invocation so the function
can be picked out (ours is normally the largest - for `sellExcessGoods` 42 candidates against the
resolver-template flood at 33, which identifies it in one run with no source edits), and `--invocation N` dumps
the table. For `sellExcessGoods`:

| score | name | | score | name |
|---|---|---|---|---|
| +104 | `amount` | | -4 | `variance` |
| +88 | `aicIndex` | | -26 | `resourceOffset` |
| +88 | `j` | | -34 | `resourceType` |
| +42 | `aiType` | | -52 | `playerResourceBase` |
| +72, +96, +85 | temporaries | | -134 | `this`, `playerID` |

and then a second round re-scores several of them - `this` and `playerID` from -134 to +32,
`playerResourceBase` from -52 to +97, `resourceType` from -34 to +64 and then to -2 - because the colourer
iterates, which is also why `Spillcosts` and `SpillOrDefer` run six and seven times here.

Run across the functions that had resisted every source-level hypothesis, the scores give each one a
recognisable signature:

| function | match | scores |
|---|---|---|
| `aiRecruitUnits` | 50.0% | `buildingID` +188, `unitID` +174, `unitType` +51, `recruitInterval` +47 against `recruitDiggingUnit` **-335**, `i` **-279**, `behaviourType` -251, `recruitCount` -197 |
| `decideOnTribeAttackLocation` | 68.8% | `destinationTile` +122, `tribeID` +93, `destinationY` +58, `destinationX` +42, `buildingID` +42, `targetPlayer` +40, `this` -1 |
| `recruitHarrassingSiegeEngines` | 73.2% | everything positive and bunched: `unitID` +44, `tribeID`/`engineIndex`/`buildingID` +36, `aiType` +32, `siegeEngineToBuild` +26, `harrassingSiegeEnginesMax`/`this` +21, `aicIndex` +11, `playerID` +9, `engineersGuild` +2 |
| `planToBuy...SnoozeBuildings` | 90.3% | the fourteen `allowX` locals all **negative** at first (-20 to -94) with only `playerID` +46 and `wood` +26 positive; a later round flips some to +48 while `allowWells` stays worst (-94, -93, -76, -43) |

Three different diagnoses fall out, where before all four looked like the same "allocator noise":

* `recruitHarrassingSiegeEngines` is decided by **near-ties** - four candidates at +36, two at +21. With equal
  scores the order falls to the symbol-id tiebreak, so no source change states a preference and small edits flip
  the result arbitrarily. That matches it resisting every targeted attempt.
* `aiRecruitUnits` has a **structural** difference: our loop counter `i` is a candidate at -279, where the
  original reuses the dead `playerID` parameter as its counter and so has no such candidate competing at all.
* `planToBuy` is **iteration-dependent** - the locals that matter start negative and only become positive in a
  later colourer round, so its layout is decided by the spill rounds rather than by a single ordering.

That makes the register side measurable per variable. `playerID` scoring -134 in the first round is why our build
serves it late and leaves it in a volatile register (`edx`), where the original keeps it in `ebp` from the start;
the question "did this source change move `playerID` up the list?" can now be answered with one trace instead of
being inferred from a register permutation in the reccmp diff.

### ChoosePhysReg decoded: a cost minimisation

The pick is not a bit-scan over a narrowed mask - that reading was wrong, and so was the note here calling
`0x10ce5a08` "not a per-register preference table". It is a table of **per-class candidate lists**, which is why
it holds pointers; class 0, the integer class, reads `eax, ecx, edx, esi, edi, ebx, ebp` - volatiles first, then
callee-saved, `esp` excluded. The rule, from `P2/color.c`:

```c
cost[] = 0                                        // array at 0x10d14f10, indexed reg*4, per pick
for each interfering candidate g with g->benefit > 0:
    for each (reg, count) preference pair of g:
        cost[reg] += count;                       // a neighbour wanting reg makes reg dearer
    if g has exactly one legal register R:
        cost[R] += g->benefit * 100;              // taking R from a single-choice neighbour is expensive
for each (reg, count) preference pair of this candidate:
    cost[reg] -= count;                           // our own affinity makes reg cheaper
pick = the register in classList[class] that is legal here with the lowest cost
       (ties to the earlier class-list entry)
```

`reg_scores.py --whyreg` dumps that array at each pick. For `sellExcessGoods`:

```
candidate            got   eax    ecx    edx    ebx    esp   ebp   esi    edi
aicIndex             eax   [0]    2      0      0      0     0     0      0
j                    edx   0      2      [0]    0      0     0     0      0
variance             edi   0      2      0      0      0     0     0      [0]
resourceOffset       ebx   0      2      0      [0]    0     0     0      0
playerResourceBase   edx   0      2001   [0]    0      0     0     0      0
this                 ecx   0      [-1]   1      0      0     0     0      0
playerID             edx   0      0      [-1]   0      0     0     1200   0
resourceType         ebx   -1     0      0      [-1]   0     0     0      0
```

Every entry is accounted for: `ecx` costs 2 for everyone because `this` has a thiscall affinity to it, and `this`
takes it at -1 because its own affinity subtracts; `playerID` sees `esi` at 1200, which is
`playerResourceBase`'s benefit of 12 times 100, a neighbour with one register left; the zeros are ties and fall
to class-list order, which is why `aicIndex` lands in `eax`.

So the counterfactual is arithmetic. To move `playerID` out of `edx` into `ebp`, `ebp` needs a cost below -1,
i.e. `playerID` needs an affinity to `ebp` worth 2 or more.

### Attributing each cost term: `--whycost`

"`ebx` costs 1100" is not yet a statement about the source. Three instructions do the accumulating -
`0x10b14c2c` adds a neighbour's preference count, `0x10b14caa` adds `benefit * 100` when a neighbour has one
legal register left (`ebx` holds that neighbour), and `0x10b14d59` subtracts this candidate's own affinity - so
breaking on them and reading the neighbour's name attributes every term. `--whycost` does that:

```
aiRecruitUnits
  playerID -> ebx
      ebx   total  +13800   PIN +800 by (temp); PIN +300 by (temp); PIN +100 by (temp)
  (temp) -> edx
      ebp   total   +4700   PIN +300 by (temp); PIN +1400 by behaviourType; PIN +1000 by i
      edx   total   +1600   PIN +1600 by this
```

The useful line is the second: **`ebp` is expensive for everyone because `behaviourType` pins it with 1400 and
`i` with 1000**. Those are named source variables, and it is a stronger statement than their own bad scores -
they do not merely lose their own pick, they make `ebp` cost 2400 more for every other candidate. It also
explains why removing `i` by counting `recruitCount` down lost ground: that just moves the pin to
`recruitCount`.

The same run on `sellExcessGoods` is the cautionary half:

```
  playerID -> edx
      esi   total   +1200   PIN +1200 by (temp)
      edx   total      -1   OWN -1 by itself
```

The 1200 is charged by a **compiler temporary**, not by a named local - an earlier note here guessed it was
`playerResourceBase` because its benefit of 12 times 100 matches, and that was a coincidence. Attribution is
what tells the two apart, and only a named source variable is something a programmer can act on.

### Acting on the attribution: measured, and it does not pay

`--whycost` named `behaviourType` (+1400) and `i` (+1000) as the two source variables pinning `ebp` in
`aiRecruitUnits`, so the indicated edit is to stop them being separate candidates. Every form of that was tried
against reccmp, from a 50.0% baseline:

| edit | match |
|---|---|
| baseline | **50.0%** |
| `recruitDiggingUnit` as `bool` | 49.5% |
| count `recruitCount` down, drop `i` | 48.7% |
| narrow `behaviourType` into the loop | 48.9% |
| narrow both `behaviourType` and `unitType` | 36.6% |

All five lose, and the tool explains why - which is the part worth keeping. Re-running `--whycost` on the
narrowed variant shows `behaviourType`'s pin went **up**, from +1400 to +1600, and `ebp`'s total from 4700 to
4900. Benefit is uses per unit of live range, so shortening a live range with the same uses *raises* the
benefit, and the pin is `benefit * 100`. The three levers therefore all fail for the same reason, coherently:

* narrowing a range raises the benefit, so the pin gets dearer;
* deleting a candidate moves the pin to whatever replaces it (`recruitCount` took it over);
* widening a range adds interference instead.

So the pin cannot be reduced from the source at all: only *fewer uses* would lower it, and the uses are what
the function has to do. `aiRecruitUnits` at 50.0% is a local optimum under every lever this model exposes, and
that is now a derived statement rather than five failed guesses.

See [reading-reg-scores.md](reading-reg-scores.md) for a plain-language walkthrough of the output.

So across the three functions measured: `recruitHarrassingSiegeEngines` charges nothing at all (pure class-list
order, nothing to act on), `sellExcessGoods` is pinned by temporaries (nothing to act on), and `aiRecruitUnits`
is pinned by `behaviourType` and `i` (something to act on, if the computation can be restructured so those
values do not exist as separate candidates).

### Why there is still no source-level fixer

The benefit is a property of what the code *does*, not of how it is written. It counts uses weighted by block
frequency, so none of the levers that cost nothing semantically - declaration order, statement order, renaming,
redeclaring - can move it. That is the reason every syntactic hill-climb in this repo has failed to shift a
register assignment, and it means a tool cannot be asked to "fix" a register mismatch by rewriting syntax.

Affinities are the only term a programmer could hope to influence, and they come from **copies between a value
and a fixed register**: a parameter arriving, an argument passed in a particular slot, a return value in `eax`,
`this` in `ecx`. That is a semantic property - where a value crosses a call boundary - and for the
*callee-saved* registers it is barely reachable at all, because affinities to `ebx`, `ebp`, `esi` and `edi` come
from copies the allocator itself inserts rather than from anything the source states. The interference term is
likewise a property of which values are simultaneously live.

What the numbers do support is a sharper statement of the problem. For an `alloc-only` function either

* our use counts differ from the original's, in which case the fix is to restructure the computation so each
  value is used the same number of times in the same places - `aiRecruitUnits` carrying a loop counter the
  original does not have is this case - or
* our use counts already match, in which case what remains is the symbol-id tiebreak and the function is
  unreachable from the source. `recruitHarrassingSiegeEngines`, with four candidates tied at +36, is this case
  and should be abandoned.

`reg_scores.py --rankdiff` tells you which of the two you are in, per variable. It pairs our benefit ranking
with the callee-saved save order on both sides - registers are consumed in the order they are first needed, so
the push order *is* the consumption order, and it comes free from the last reccmp run. For `sellExcessGoods`:

```
our benefit ranking:        1 amount 70   2 variance 22   3 resourceType 20   4 resourceOffset 20 ...
consumption order  original: ebp edi ebx esi
                   ours:     esi ebx ebp edi
```

Both sides use the same four registers, so the candidate *set* matches and neither side carries a value the other
does not - that much is solid, and it rules out the `aiRecruitUnits` case for this function. What the permutation
*means* cannot be settled from here: either our candidates are ranked differently, or they are ranked the same
and `ChoosePhysReg` narrowed the mask differently. The tool says so and labels the pairing a hypothesis rather
than a finding, because the mask narrowing is undecoded. It also flags the degenerate case where the two orders
are exact reverses, which would be systematic rather than per-candidate.

So the honest scope of the "fixer" is: it decides set-mismatch against order-mismatch, names the candidate that
would have to be re-ranked under the ranking hypothesis, and states what that would cost (a change in weighted
use counts, which is a change in what the code does). It is a decision procedure, not an automatic rewrite, and
the last step from "this candidate is mis-ranked" to "therefore edit this line" needs the mask narrowing decoded
first.

### Do the suggestions prescribe a fix? Measured: no

`reg_scores.py --advise` names the patterns above and suggests what to try. Those suggestions were then tested
against reccmp on `aiRecruitUnits` (50.0%), the function with the strongest structural signal - a loop counter `i`
at -279 and a flag `recruitDiggingUnit` at -335 against a +188 top candidate:

| variant | suggestion acted on | match |
|---|---|---|
| baseline | - | **50.0%** |
| count `recruitCount` down, drop `i` | DISFAVOURED loop counter | 48.7% |
| `recruitDiggingUnit` as `bool` | DISFAVOURED flag, and Ghidra renders it `bool` | 49.5% |

Both lost ground. Removing a disfavoured candidate changes the whole scoring landscape - fewer candidates means
different spill rounds - so "delete the worst one" is not a monotone improvement, and the scores diagnose without
prescribing.

What the scores are reliably good for is **triage**, including the negative verdict. A function whose candidates
share scores (`recruitHarrassingSiegeEngines`: four at +36, two at +21) cannot be steered from the source at all,
because the order falls to the symbol-id tiebreak - so the correct action is to stop working on it. That is worth
knowing before spending an afternoon on hill-climbing, even though it never adds a percent.

Still not decoded: how the score itself is computed, and what narrows `ChoosePhysReg`'s mask before the `bsf`.
One dead end recorded so it is not retried: the table at `0x10ce5a08`, indexed by `eax * 4` in `ChoosePhysReg`,
holds pointers and runs into unrelated data after a few entries, so it is not a per-register preference table.

## Debugger harness

`cl.exe` is 32-bit, so use the x86 `cdb` (`C:\Program Files (x86)\Windows Kits\10\Debuggers\x86\cdb.exe`).
`c2.dll` loads **unrebased** at `0x10b00000`, so PDB addresses work directly as breakpoints and cdb never needs to
load symbols. `c1xx.dll` and `c2.dll` run in-process, so no child-process debugging is needed.

```
sxe ld:c2
g
r $t0=0
bp1 0x10b04fa0 ".printf \"IT arg=%08x\\n\", @eax; gc"
bp2 <ret address> ".printf \"  ret %d\\n\", @eax; gc"
bd 1-7
bp0 0x10c07350 "r $t0=@$t0+1; .if (@$t0==0n613) { be 1-7 }; .if (@$t0==0n614) { bd 1-7 }; gc"
g
q
```

Four things learned the hard way:

* One TU of ours costs about **1455 `GlobalRegAlloc` invocations and 118k iterator calls**. Leave the inner
  breakpoints **disabled** and let the outer one enable them for the invocation of interest; seven enabled
  conditional breakpoints blew a 900-second timeout, the disabled form finished comfortably.
* `gu` inside a breakpoint command makes cdb skip the rest of that command ("previous commands caused target
  execution inside an event handler"). To read a return value, break on the function's `ret` instead.
* Nested `.printf` quoting breaks the outer parse. Keep every breakpoint command one level deep and gate it on a
  pseudo-register flag that the outer breakpoint sets.
* When taking `ret` addresses from a disassembly, bound the scan to the function. Reading 400 bytes and taking the
  first six `ret`s crossed into neighbouring functions and produced 1210 "returns" from 532 calls, with pointer
  values posing as register numbers.

**Identifying the invocation** is the fiddly part: hundreds of resolver-template instantiations allocate
identically (exactly 463 iterator calls each), so size alone does not single out the function. Compile the file
twice, with the function's body replaced by `return;` the second time, and find the invocation whose count drops
by the total difference. For `sellExcessGoods` the total fell by 524 and the matching invocation was #613 at 532
calls; re-running with the breakpoints armed captured exactly 532, which confirms it.

## Order of work, and where reccmp belongs in it

The match percentage is the goal, but it is a poor instrument for most of the way there, because it is
dominated by register and stack-slot *naming* - terms the source cannot state. Worse, it moves against
real progress: adding a local that the original has shifts every `[esp + N]` displacement in the function,
and each of those is scored as a mismatch until the layout lines up, so a correct change reads as a
regression. Work in this order instead, and each step has an instrument that is immune to the next step's
noise:

1. **Frame size and slot layout** - `slot_map.py FILE.cpp`. Compares our `/FA` slot table against the
   layout inferred from the original's disassembly: offsets, sizes, reference counts and the sort key.
   A frame that is too small is a missing local, and the reference counts say which local is in the wrong
   place. Independent of every later step.
2. **Instruction mix** - `structural_diff.py NAME`. `delta` names concrete defects ("we emit two `xor`
   the original does not"); `kind` is the bare mnemonic sequence. Independent of register naming.
3. **Statement order** - the same `kind` tier, once `delta` is zero. This is what took the sixteen
   `setAICParameters_NN` functions to 100%.
4. **Register and slot naming** - only now is the percentage the right objective, because it is all that
   is left. `reorder_search.py` and `perm_decls.py` hill-climb on it.

The reason this ordering works is that the earlier steps are *causes* and the later ones are *effects*:
register allocation is deterministic given the compiler's IR, so an identical instruction stream in an
identical frame allocates identically. Chasing the effect while the cause is still wrong is what makes a
function feel stuck.

A worked case of the instruments disagreeing, and of trusting the right one, is below: on
`renderDebugDataAiInfo` the frame went from wrong to byte-exact - all seven slots, every offset and every
reference count - while reccmp *fell* by 0.9 points.

## Frame size as a local-count oracle

`sub esp, N` in the prologue is the one number in the original that states, directly and without any
allocation noise, **how much stack the original function's locals occupy**. It is worth checking first,
because a mismatch there is a missing or surplus local and no amount of statement reordering will fix it.

Worked example, `AICState::renderDebugDataAiInfo` (`0x004d1320`). The original opens `sub esp, 0x400`; our
version opened `sub esp, 0x3f8`, so the original had 8 bytes - two dwords - of locals we did not. Two
independent instruction-mix defects pointed at the same two values:

* `this->aics[aiType - 1]` appeared at three call sites, each emitting its own `imul reg, reg, 0x2a4`.
  The original emits that `imul` **once**, and earlier stores `aiType - 1` to a slot (`add ecx, -0x1;
  mov [esp+N], ecx`). Caching the index in a local collapsed three `imul` to one.
* the original *also* caches the resulting element address: `add eax, ecx; mov [esp+N], eax`, read back
  later as `mov ecx, [esp+N]; add eax, [ecx + 0x1f4]`. That is the second dword.

Adding the two locals took the frame from `0x3f8` to exactly `0x400`, the instruction-mix delta from 13 to
3 and the mnemonic-sequence similarity from 0.943 to 0.979. The frame size is what told us *how many*
locals to look for; the mix told us *which*.

The caveat is that the frame also moves when the compiler spills, so a frame that is too small is strong
evidence of a missing local while a frame that is too large can be either a surplus local or a spill.

## The mode flag at 0x10d0ffdc is not a lever, and neither pragma pays here

`FUN_10b10420` switches the penalty on `cmp dword ptr [0x10d0ffdc], 2` - `key -= weight` when it
equals 2, `key -= count * weight` otherwise - which raised the obvious question of whether the
original was simply compiled in the other mode. It was not, and the flag is not reachable from the
source:

* measured during our own compile, with a breakpoint on `dop2_GlobalRegAlloc` printing it:
  **`MODEFLAG 0`**. So we take the larger `count * weight` penalty.
* `#pragma optimize("s", on)` does **not** change it - still 0 - so it is not the per-file
  size/speed switch. It is read in about 400 places and is set at invocation level.
* and size-favoured code is plainly not what the original used anyway: that pragma takes
  `aiGiveRaidInstructions` from 241-vs-234 instructions and a mix delta of 7 to 205 instructions
  and a delta of **52**, with the quick_diff ratio collapsing 0.728 -> 0.372.

So both sides compute the key with the same formula, and the ranking difference is not a flag.

The two pragmas that the cheat sheet records as sometimes winning were also measured here, and both
**do** fix the structural defect while losing more than they gain. `aiGiveRaidInstructions` is
missing one copy of its tile computation because MSVC cross-jumped three identical `if`/`else` arm
tails into one, and the original kept two:

| variant | quick_diff ratio | mix delta | `imul 0x32c` (original has 4) | `this` lands in |
| --- | --- | --- | --- | --- |
| as committed | **0.728** | **7** | 3 | ebp |
| `optimize("y", off)` | 0.262 | 10 | **4** | edi |
| `inline_depth(1)` | 0.708 | 15 | **4** | ebp |
| both | 0.253 | 26 | **4** | edi |
| `optimize("s", on)` | 0.372 | 52 | 4 | - |

`optimize("y", off)` restores the duplicate exactly as its cheat-sheet entry predicts - it is the
pragma that stops `/Oy` cross-jumping identical sequences - but it also reserves `ebp` as a frame
pointer, which moves `this` to `edi` and rearranges everything. The original uses `ebp` as a
general register (`mov ebp, [esp+N]; imul ebp, ebp, 0x39f4`), so `/Oy` has to stay on, and with it
on the cross-jump happens.

Why it cannot be separated: the original's two copies are the same instructions in *different*
registers -

```
copy A   lea edx, [ecx + ecx*2]   add eax, dword ptr [edx*4 + 0x2337300]
copy B   lea ecx, [ecx + ecx*2]   add eax, dword ptr [ecx*4 + 0x2337300]
```

Cross-jumping runs after register allocation, so in the original it was the differing registers
that made the two tails non-identical and saved them from being merged. Ours were allocated the
same registers and merged. The duplicate and the `ebx`/`ebp` swap are therefore one coupled
phenomenon, not cause and effect - an earlier note in this file claimed the duplicate was upstream
of the register swap, which this corrects. Rewriting the expression does not break the tie either:
commuting the addition in one arm only, so its text differs, changes nothing because MSVC
canonicalises it.

What did pay on that function was an ordinary source defect the mix delta pointed at by
subtraction: delta 9 decomposed as the seven-instruction duplicate plus a leftover `je -1, jne +1`,
which is one inverted branch. The final `if` tested the navigation result the opposite way round,
and swapping its arms took it **56.8% -> 60.3%**. `diff_jcc.py` does not catch that because it
covers strictness steps and operand order, not a plain polarity flip - worth adding.

## The ordering key decoded: a per-region benefit/penalty balance

`+0x0c` is accumulated at the tail of `FUN_10b10420`, which the colourer calls for each register
class just before it builds the ordered list. The call chain is

```
dop2_GlobalRegAlloc   0x10c07350   driver
  -> colourer         0x10b0cf40   loops register classes 6..0
       -> 0x10b0ded0               live ranges
       -> 0x10b10420               ** accumulates +0x0c **
       -> 0x10b11560, 0x10b11770   walks the symbol hash table, calls InsertInList per candidate
            -> 0x10b16720          interference, per block
                 -> 0x10b16bd0     interference, per instruction
  -> ChoosePhysReg    0x10b14e2a   picks the cheapest free register
```

and the accumulation itself is:

```
0x10b1145b  add  edi, 1            ; count every element of list A
0x10b11476  add  edi, 1            ; plus list B elements carrying flag 0x10
0x10b11484  imul edi, ebp          ; ebp: a weight passed in - block frequency
0x10b11489  mov  esi, edi          ; esi = count * weight

; a candidate REFERENCED in this region:
0x10b11495  mov  ecx, [eax+0x18]   ; its reference multiplier for the region
0x10b11498  imul ecx, esi
0x10b1149b  add  [eax+0xc], ecx    ; key += refs * count * weight
0x10b114a2  mov  [eax+0x18], edx   ; reset the multiplier

; a candidate LIVE here but NOT referenced:
0x10b114d2  cmp  dword ptr [0x10d0ffdc], 2
0x10b114db  sub  [eax+0xc], ebp    ; key -= weight          (when that global is 2)
0x10b114e0  sub  [eax+0xc], esi    ; key -= count * weight  (otherwise)
```

So the key is **not** a use count. It is a balance taken region by region: a value gains
`refs * count * weight` where it is used, and is **penalised** `count * weight` for every region
it is live across without being referenced. A register held open through code that does not touch
it is charged for.

That predicts the numbers we measured, which is the check worth doing. On
`aiGiveRaidInstructions` `playerID` comes out at **-147** - live across the whole loop and barely
read inside it - and `i` at **1**; both are among the locals `slot_map.py` independently shows in
stack slots, and the negative-key candidates are exactly the spilled set.

**The consequence is that the key depends on the block structure, not just on how often a value
is named.** Two source versions with identical reference counts can rank differently if their
regions differ. That resolves the `aiGiveRaidInstructions` question left open above: our base
temporary outranks `this` (128 against 93) while the original's `this` won `ebx`, and the two
binaries reference those values an identical 27 and 22 times - but our block structure still
differs, because we emit one copy of the tile computation where the original emits two, which is
one region fewer. The register swap is downstream of that mix defect, which is what
`structural_diff.py` reports from the divergence positions alone.

So the lever for that function is the duplication, not anything register-side. Moving `i` into
the `for` initialiser reached delta 3 but disturbed too much else (56.8% -> 44.1%); what is wanted
is the missing duplicate on its own.

A note on tooling for this kind of chase: REA runs Ghidra in an ephemeral isolated project, which
decompiles `c2.dll` without touching a shared Ghidra session's `currentProgram`. It will not load
a caller-supplied PDB, though, so symbol names are absent - `FUN_10b10420` and friends are as good
as it gets, and the `P2/*.c` assert strings are what anchor a function to its source file
(`FUN_10b133e0` reports `P2/color.c` line 0x1b37). For named symbols a separate Ghidra project
with `c2.pdb` alongside would be the escalation.

## Correction: the candidate ordering key is +0x0c, not +0x40

An earlier version of these notes said `InsertInList` sorts candidates on `+0x40`, a weighted use
count, and that `+0x0c` was only a tie-break. That is backwards, and it sent a whole afternoon of
work on `aiGiveRaidInstructions` chasing the wrong number. Disassembling `@InsertInList@8` at
`0x10b11970` settles it:

```
0x10b1197f  mov ecx, dword ptr [edi + 0xc]     ; the candidate already in the list
0x10b11983  mov esi, dword ptr [eax + 0xc]     ; the one being inserted
0x10b11986  cmp esi, ecx
0x10b11988  jg  0x10b119e3                     ; greater goes first - descending on +0x0c
0x10b1198a  jne 0x10b11994
0x10b1198c  mov ecx, dword ptr [eax + 0x44]    ; tie on +0x0c: compare the symbol id
0x10b1198f  cmp ecx, dword ptr [edi + 0x44]
```

**Primary key `+0x0c`, descending; tie-break `+0x44`, the symbol id.** `+0x40` is a separate
weight that does not decide the order.

Where the old claim came from: there is a *second*, very similar insert function immediately
after this one, at `0x10b119f0`, and that one does sort on `+0x40` - and it *writes* `+0x0c`,
copying it from a neighbouring record:

```
0x10b11a49  mov edi, dword ptr [edx + 0x40]
0x10b11a4c  cmp edi, dword ptr [ecx + 0x40]
...
0x10b11a63  mov eax, dword ptr [eax + 0xc]
0x10b11a67  mov dword ptr [edx + 0xc], eax
```

The two are easy to confuse. The one the harness breakpoints, and the one whose candidates match
the function being compiled, is `0x10b11970`.

**How to verify which field orders the picks**, rather than trusting either note: dump both
fields per candidate and compare each ordering against the actual sequence of register
assignments from `--whyreg`. On `aiGiveRaidInstructions` the picks went `tile`, temp, 
`targetBuildingID`, temp, temp, `this`, `buildingID` x3, `y`, `x`:

| field | order it predicts | matches the picks? |
| --- | --- | --- |
| `+0x0c` | tile 212, temp 148, targetBuildingID 140, temp 128, temp 108, this 93, buildingID 88, y 80 | **yes, exactly** |
| `+0x40` | temp 82, this 60, tile 52, i 46, temp 44, tribeID 44 | no - puts `this` and a temp ahead of `tile` |

`+0x0c` reads as a *net* benefit: the values that come out low or negative (`i` at 1,
`playerID` at -147) are exactly the ones `slot_map.py` shows living in stack slots, so the two
tools cross-check each other.

A dead end worth not repeating: trying to find the code that *computes* `+0x0c` by taking a
candidate record's address from one run and arming `ba w4 <addr>+0xc` in the next. The records
are heap-allocated and the addresses are **not** stable between runs - the watchpoint fired
inside `ntdll!RtlpFreeHeap` and the record read back a symbol id of `311b11c`. The address has
to be captured and the watchpoint armed within a single run, which needs a breakpoint command
that stops rather than continuing (omit the trailing `gc`) so the script regains control.

Also: a linear capstone sweep of `c2.dll`'s `.text` stops at the first byte it cannot decode,
which gave 12106 instructions out of a 1.9 MB section and made a scan for field writes look
almost empty. Resync by skipping one byte and continuing; the real count is 647653, with 291
writes to `[reg + 0x40]` and 2543 to `[reg + 0xc]`.

## What this does and does not unlock for aiGiveRaidInstructions

The function's remaining register gap is a clean two-cycle: the original keeps `this` in `ebx`
and `playerID * 0x39f4` (the player-record base) in `ebp`; ours has them swapped, which accounts
for 46 of its 70 differing operands. `ebx` precedes `ebp` in the class list, so whichever is
served first takes it, and with the corrected key our base temporary sits at **128** against
`this` at **93** - so the temporary is served first and takes `ebx`.

For the original to have given `this` `ebx`, its `this` must have outranked its base temporary.
Both binaries reference those two values an identical 27 and 22 times, and the call pattern is
identical on both sides (14 `mov ecx, <this>` plus 3 `mov ecx, <global>`), so there is no
difference in use counts to exploit. `this` is a genuine `__thiscall` parameter in both - the
original does `mov ebx, ecx`, ours `mov ebp, ecx` - so this is not a case of the object being
reached as a global instead.

Three source forms were measured and all rejected:

| change | effect |
| --- | --- |
| `PlayerData& pd = ...playerDataArray[playerID]` used throughout | base moves to `esi`, `this` stays in `ebp`; quick_diff ratio 0.695 -> 0.499 |
| `AICState* self = this;` for the member calls | byte-identical output, the optimiser folds it |
| `i` moved into the `for` initialiser | mix delta 9 -> 3, but 56.8% -> **44.1%** |

So the ordering key is now known and measurable, and it says the two values are ranked the way
they are for reasons that are not expressible in the source. What would settle it is the formula
behind `+0x0c`, which is still open - the write that computes it has not been located, only the
two places that copy it.

## Register allocation is an effect, not a cause

The register names in a near-matching function are not a problem to be attacked directly, and
`ChoosePhysReg` says why. Dumping the per-register cost array at every pick in
`renderDebugDataAiInfo` (invocation #800, 41 candidates) gave **all zeros** for every volatile
pick:

```
candidate              got   eax     ecx     edx     ebx     esp     ebp     esi     edi
(temp)                 esi   0       0       0       0       0       0       [0]     0
y                      edi   0       0       0       0       0       0       0       [0]
x                      ebx   0       0       0       [0]     0       0       0       0
color                  ebp   0       0       0       0       0       [7500]  0       0
siegeTroops            eax   [0]     0       0       0       0       0       -1      0
castleID               eax   [0]     0       0       0       0       0       0       0
```

With the costs tied at zero the minimisation is vacuous and the winner is simply the first free
entry in the class list - `eax, ecx, edx, esi, edi, ebx, ebp`. Nothing about how the source is
spelled or typed enters into it. The only inputs left are the order candidates are served
(score descending, then the symbol-id tiebreak) and which registers are still live at that
point, and both of those are decided by the instruction stream.

That makes the useful question not *which* registers differ but **where** they start to
differ, which `structural_diff.py` now reports:

| | `renderDebugDataAiInfo` | `aiCreateSiegeUnits` |
| --- | --- | --- |
| instructions aligned on the register-stripped skeleton | 293 of 305 | 319 of 322 |
| first structural difference | instruction 139 | instruction 30 |
| first register difference | instruction 152 | instruction 223 |
| dominant substitution | `eax -> edx -> ecx -> eax`, 90% of 59 | `esi <-> ecx`, 2 |

In both cases the registers diverge *after* the structure does, and in
`renderDebugDataAiInfo` the first 149 instructions have identical registers while the
callee-saved assignments - `ebx` for `x`, `edi` for `y`, `esi` for the player base, `ebp` for
the colour - are identical throughout. A substitution set that closes into a cycle is the
signature of this: the allocation is structurally right and the scratch registers were handed
out in a different order, which happens as soon as one extra or missing instruction changes
what is live.

So the rule is: if the first register difference is at or after the first structural
difference, the register names are an effect of that structural defect and will follow once it
is fixed. Spending effort on them while a mix defect remains is spending it on a symptom. The
converse case - registers diverging *before* any structural difference - is the one worth
investigating, and there the lever is statement order, because that is what sets both the
serve order and the liveness.

## MSVC hoists the maximal common expression, which decides how to write it

When the same expression appears in both arms of an `if`/`else`, MSVC's global optimiser hoists it
above the branch - and it hoists as *much* of it as is common, which is the part that matters when
matching. `renderDebugDataAiInfo` has two `sprintf` calls differing only in the format string. The
original duplicates the whole argument setup in each arm:

```
imul eax, eax, 0x6d98              ; shared: the AIV index, scaled
cmp  dword ptr [esi - 0xdf4], 0
jne  arm_b
mov  eax, dword ptr [eax + 0x1866ac0]   ; arm A: load castleID, base folded in
add  eax, 1
push eax
push 0x5aad50                      ; "AIV:n/a"
lea  ecx, [esp + 0x2c]
push ecx
jmp  shared_call
arm_b:
mov  edx, dword ptr [eax + 0x1866ac0]   ; arm B: the SAME load again
add  edx, 1
push edx
push 0x5aad48                      ; "AIV: %d"
lea  eax, [esp + 0x2c]
push eax
shared_call:
call sprintf
add  esp, 0xc
```

Only the `imul` is shared; the identical load is not. Writing the full expression out in both arms
does **not** reproduce that - MSVC hoists the load, the `add`, the value `push` and the `lea` of the
buffer above the `cmp`, leaving just `push OFFSET <string>` per arm. Four forms were tried and all
four hoisted: the expression inline in both arms, a shared local assigned before the branch, a local
declared before and assigned separately inside each arm, and a ternary on the format string. (The
`push` moving above the branch is worth noticing on its own - a post-allocation peephole cannot move
a push across a branch, so this is the global optimiser, before register allocation.)

The reason is the *extent* of the common expression. Written out twice, the whole chain
`playerDataArray[playerID].aivID` -> `* 0x6d98` -> load `castleID` -> `+ 1` is common, so all of it
is hoisted. The original shares only the front of that chain, which is what you get when **the source
holds the index in a local** and writes the array access out in each arm:

```cpp
int aivID = DAT_GameState::instance.playerDataArray[playerID].aivID;
if (...) sprintf(text, "AIV:n/a", DAT_AIVState::instance.aivs[aivID].castleID + 1);
else     sprintf(text, "AIV: %d", DAT_AIVState::instance.aivs[aivID].castleID + 1);
```

The index is shared because the source shares it; the two loads are left alone. That took the function
from 305-vs-302 instructions and a mix delta of 3 to **305 against 305 with a delta of 0**, and
reccmp from 67.5% to 83.6%.

A pointer or reference local to the element gets close but not there - delta 1, because it keeps the
address as a value and pays an `add` to materialise `base + index * size`, where the original keeps
only `index * size` in the register and re-folds the array base into each load's displacement:

| form | mix delta | instructions | note |
| --- | --- | --- | --- |
| expression inline in both arms | 5 | 300 | whole chain hoisted |
| shared local before the branch | 3 | 302 | hoisted by construction |
| `AIVSpec*` / `AIVSpec&` to the element | 1 | 306 | extra `add` for the address |
| **index in a local** | **0** | **305** | matches |

The general rule: to get a computation duplicated per arm, share in the source exactly the prefix the
original shares, and write the rest out. Sharing less gets the whole thing hoisted; sharing more - a
pointer where the original had an index - adds the instruction that materialises what you shared.

## A defect class: which constant gets the callee-saved register

`updateAIPlayerState` (78.6% with resolvers off, 81.7% with them on) is structurally almost
perfect - 483 instructions against 486, `kind` 0.989 - and its whole mix delta of 3 is
`xor +2, mov +1`. The cause is worth recording because it is a distinct class from the defects
already in this file, and because the obvious source fix does not work.

A census of the two streams:

| | immediate dword stores | `xor r, r` zeroings | `mov r, 1` |
| --- | --- | --- | --- |
| original | `0x9` x3, `0x5` x2, `0x1` x1, `0x8`, `0x7`, `0x2` - **no `0x0` at all** | **1** | 1 |
| ours | `0x9` x3, **`0x0` x3**, `0x5` x2, `0x8`, `0x7`, `0x2` | **3** | 2 |

The source has fourteen `= 0;` assignments and one `= 1;`. The original keeps **0** in `ebp` for
essentially the whole function and never stores it as an immediate; we keep **1** there and
materialise 0 three separate times.

Where it starts is exact. Both sides are identical for 45 instructions, including

```
36  mov ebp, dword ptr [edi + G]     ; ebp = _aiPlayerState
37  test ebp, ebp
40  jne L                            ; so on the fallthrough ebp is known to be 0
```

and then diverge immediately:

```
original                              ours
46  mov dword ptr [edi + G], ebp      46  xor eax, eax
47  mov dword ptr [edi + G], 0x1      47  mov ebp, 0x1
48  mov dword ptr [edi + G], ebp      48  mov dword ptr [edi + G], eax
49  mov dword ptr [edi + G], ebp      49  mov dword ptr [edi + G], ebp
```

The original reuses the register that already holds `_aiPlayerState` - known zero on this path -
for all three zero stores, and writes the literal 1 as an immediate. We materialise a fresh zero
in `eax` and **clobber** the known-zero `ebp` with the constant 1. The same inversion then runs
through the whole function: every `xor ebp, ebp` in the original is a `mov ebp, 0x1` in ours, and
the original's `add dword ptr [...], 0x1` is our `add dword ptr [...], ebp`.

**The obvious fix fails.** Inside `if (_aiPlayerState == 0)` the local is zero, so writing
`attackTicker = _aiPlayerState;` instead of `= 0` is semantically identical and ought to force the
reuse. It produces **byte-identical** output - quick_diff 0.8669 either way, delta still 3.
Constant propagation replaces `_aiPlayerState` with 0 before allocation ever runs, so the source
cannot express the difference; the compiler knows the value is zero in both spellings and still
chooses to dedicate the callee-saved register to 1.

So this is a third symptom of the same underlying thing as the frame and pressure walls: the
allocator's choice of what to keep in a callee-saved register, decided by the `+0x0c` keys, with
no source handle. What is new is the *signature* - a small `xor` surplus with matching immediate
stores, and an `xor r,r` against `mov r,1` at the same instruction on both sides - which is worth
recognising, because it looks like a code-shape defect and is not one. If a function shows
`xor +N` with the stores otherwise matching, check whether the original is reusing a known-zero
variable's register before looking for a source cause.

## Two slot-layout leads that were not source defects

Both functions whose frames still disagreed after the jump-table fix turned out not to be
source problems, and the way each failed is worth keeping.

**`aiCreateSiegeUnits` (96.9%) was a tool artifact.** It reported 13 slots against our 12, with
one at **-52 inside a 0x30 frame** - an offset past the end of what the prologue allocated,
which is arithmetically impossible. The cause is visible in its own warning: two paths reach
`0x4d23a7` with esp depths 4 apart, so the depth tracking drifted and invented a slot.
`slot_map.py` now excludes references below `-frame` and says so, with the explicit note that a
slot-count difference on a function reporting a depth conflict must not be read as a defect.
With the phantom gone both sides show 12 slots at matching offsets, and the function's real
residue is the 2-instruction `jmp` delta it already had.

That is the third artifact of this kind this session - an unreferenced slot symbol MSVC emits
but never uses, switch cases unreachable without following the jump table, and now depth drift -
and they share a cause: our side is *stated* by the `/FA` listing while the original's is
*inferred*, so the inferred side needs sanity checks before any difference it reports is
believed.

**`planToBuyWhenLowOnResourceAndSnoozeBuildings` (89.9%) is a real slot permutation with no
reachable lever.** 248 instructions on both sides, frame `0x30` on both, 10 slots on both, the
same reference weights - but the locals sit in different slots, and the zero-initialising stores
come out in a different order:

```
original:  mov [esp+0x3c], edi / mov [esp+0x48], edi / mov [esp+0x38], edi
ours:      mov [esp+0x48], edi / mov [esp+0x3c], edi / ...
```

With several locals tied on weight (three at 5 references, four at 4, two at 3) this looked like
the textbook declaration-order tie-break, which is the one case `perm_decls.py` and
`quick_reorder.py` exist for. It is not: a `quick_reorder -s` hill-climb over all fourteen
declarations kept **no** move, start and final both 0.9234.

`final == start` is also what the documented concurrent-run corruption looks like, so it was
checked rather than believed - three hand-made swaps of equal-weight pairs score **0.9194**,
**0.9153** and **0.9113**, all worse. The scoring is live, and our declaration order is already
a local optimum. The residue is therefore neither weight nor declaration order, which leaves the
class byte at `+0x18` - the part of `StkColorCmp` that is still undecoded.

So the earlier guess that "a slot-count difference is more likely source-reachable than a
pressure difference" was wrong in both directions: one difference was not real, and the other is
real but sits in the one input to the sort that has not been decoded.

## Two things that do not work

**Declaration order, when there are no ties.** `StkColorCmp` sorts by class and weight and uses declaration
order only to break ties, so where the weights are distinct the declaration order is simply inert. On
`renderDebugDataAiInfo`, moving both new locals to the top of the loop body and then swapping them against
each other gave byte-identical output three times over - `67.5 / 71.0` in every case. Permuting declarations
is worth trying only once `slot_weight.py` shows an equal-weight group.

**Forcing the compiler to duplicate a computation.** The original duplicates the whole argument setup in
both arms of one `if`/`else`, using `eax` in one arm and `edx` in the other - two separate computations the
compiler never merged. Ours hoists the common part above the branch. Three source forms were tried: the
expression written out inline in both arms, a shared local assigned before the branch, and a local declared
before the branch but assigned separately inside each arm. MSVC CSE'd all three. Whatever produces the
original's duplication is not expressible by moving that expression around, so this is a dead end to stop
pushing on rather than a defect to keep chasing.

## Structural similarity and the match percentage can move in opposite directions

Measured on `renderDebugDataAiInfo`, three source forms, each a full build and reccmp run:

| form | reccmp raw / normalised | mnemonic similarity | mix delta | frame |
| --- | --- | --- | --- | --- |
| committed baseline | **68.4 / 72.6** | 0.943 | 13 | `0x3f8` |
| index cached | 66.2 / 69.7 | 0.972 | 5 | `0x3fc` |
| index and element address cached | 67.5 / 71.0 | **0.979** | **3** | **`0x400`** |

The percentage is monotone *against* the structural measures across all three points, while the frame size
says the third form is the one that matches the original's locals. The mechanism is that adding a local
shifts every `[esp + N]` displacement in the function, and reccmp scores each of those as a mismatch until
the whole layout happens to line up - so a structurally correct change can cost points for as long as the
slot layout stays wrong.

The practical consequence is that **the percentage is not a safe objective for hill-climbing while the frame
size is still wrong**, and a drop of a point or two against a confirmed frame match is not evidence the
change was wrong. It also means a correct intermediate state can look like a regression, which is a reason
to record the frame size and the mix delta in the commit message alongside the percentage, not just the
percentage.
