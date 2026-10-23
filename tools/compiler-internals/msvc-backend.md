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
`"noreg"`, which gives the internal numbering - the reverse of the x86 encoding order:

```
edi=0  esi=1  ebp=2  esp=3  ebx=4  edx=5  ecx=6  eax=7
```

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

Not decoded: what narrows the mask before the `bsf` - that filtering is the remaining question, and it is what
decides why our first candidate got `esi` where the original's got `ebp`. `@OrderGlobregs@12` runs once per
function and is the candidate-priority pass, so it is the next thing to read. A table at `0x10ce5a08` is indexed
by `eax * 4` in `ChoosePhysReg` and looked like a per-register table, but it holds pointers and runs into
unrelated data after a few entries, so that reading is unconfirmed.

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
