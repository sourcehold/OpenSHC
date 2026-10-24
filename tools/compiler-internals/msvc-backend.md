# MSVC 14.00 backend notes (`c2.dll`)

Notes on the **compiler** rather than the game: what the bundled optimizer does, how it was read, and how to
observe it. The reimplementation-facing conclusions live in
[IMPLEMENTATION_CHEAT_SHEET.md](../../IMPLEMENTATION_CHEAT_SHEET.md); this file is the evidence behind them and
the starting point for digging further.

Everything here is about `MSVC1400-SP1/VC/bin/c2.dll`, `Microsoft (R) Optimizing Compiler Version
14.00.50727.762` - the toolchain this project builds with, so it is the authority on our codegen rather than a
proxy for it.

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

Known unknown: the **class byte at `+0x18`** is the primary key and its assignment has not been decoded, so
arrays and address-taken locals interleave for reasons the model does not cover (`wrapTextIntoLines` is a
worked example of a non-monotone report).

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
