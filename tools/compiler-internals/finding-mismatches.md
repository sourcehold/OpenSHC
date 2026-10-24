# Finding out why a function does not match

This is a walkthrough of the tooling, written for someone who has never done this before. No
compiler theory needed. Two real functions are used throughout: one that went from 67% to 95%,
and one that is still stuck, because the stuck one teaches more.

## The problem, in one paragraph

The original game is a compiled `.exe`. We write C++ that is supposed to compile to **the exact
same machine code**. `reccmp` compares our compiled function against the original's bytes and
gives a percentage. When it says 56%, something about our C++ is different - but the percentage
does not say *what*, and that is the whole difficulty. The tools below turn "56%" into a
sentence like "the original computes this three-instruction sequence twice and we compute it
once".

## The one idea you need

Compiling happens in stages, roughly:

1. decide which local variables exist and where they live on the stack
2. decide which machine instructions to emit, and in what order
3. decide which CPU register holds each value

Stage 3 depends on stage 2, which depends on stage 1. The compiler is **deterministic**: same
input, same output, every time. So if our stage 1 and stage 2 are identical to the original's,
stage 3 comes out identical for free.

That gives the order of work, and it is the opposite of what feels natural:

| step | tool | what it answers |
| --- | --- | --- |
| 1 | `slot_map.py` | do we have the same local variables, in the same stack slots? |
| 2 | `structural_diff.py` | do we emit the same instructions, in the same order? |
| 3 | - | registers. **Do not work on this directly.** It usually follows from 1 and 2. |
| 4 | `reccmp_report.py` | the official percentage, to confirm at the end |

**The percentage is a bad guide until the end.** Here is the proof, measured on
`renderDebugDataAiInfo`. Adding two local variables that the original definitely has made the
stack frame go from wrong to byte-perfect - and the percentage *dropped*:

| version | reccmp | stack frame |
| --- | --- | --- |
| before | **68.4%** | `0x3f8` - wrong, 8 bytes too small |
| after | 67.5% | `0x400` - exactly right |

Why? Adding a local shifts every single `[esp + something]` offset in the function, and reccmp
counts each shifted offset as a mismatch. The change was right and the score got worse. If you
steer by the percentage you will undo correct work. (That same function later reached 95.4%,
so the frame fix was indeed on the way there.)

## Step 1: the stack frame

```
$ python tools/reimplementation-helper/batch/slot_map.py src/OpenSHC/AI/AICState/aiGiveRaidInstructions.cpp
frame   original 0x14   ours 0x14   (+0)

   off   span  acc  refs    key |    off   size  refs    key  name
   -20      4    4     9   2250 |    -20      4     9   2250  _i$
   -16      4    4     5   1250 |    -16      4     5   1250  _tribeID$462193
   -12      4    4     3    750 |    -12      4     3    750  tv694
    -8      4    4     2    500 |     -8      4     2    500  _aicIndex$
    -4      -    4     2    500 |     -4      4     2    500  _this$
```

Left is the original, right is ours. `off` is where the variable sits relative to the stack
pointer on entry, `refs` is how many times it is read or written, `name` is our variable's name
(`tv694` is a compiler-made temporary).

This is a perfect result: same frame size, same five slots at the same offsets with the same
reference counts. Nothing to do.

The interesting case is when it is *not* perfect. `sub esp, N` in the original tells you
exactly how many bytes of locals the original had, with no guesswork - and a frame that is too
small means **we are missing a local variable**, which no amount of fiddling with instructions
will fix. A `?` row means one side has a slot the other does not:

```
   off   span  acc  refs    key |    off   size  refs    key  name
 -1024      4    4     4   1000 |      ?                      <-- a local we do not have
 -1020      4    4     3    750 |      ?                      <-- a local we do not have
 -1016      4    4     3    750 |  -1016      4     5   1250  _this$GSCopy$
```

That is what `renderDebugDataAiInfo` looked like, and it is how we knew to go looking for two
missing variables.

One subtlety worth knowing: ours comes from a list the compiler prints (`/FA`), which states
every slot outright. The original's has to be *worked out* from the machine code, by tracking
how deep the stack pointer is at each instruction. That is why the tool sometimes prints a
warning instead of a table - if it cannot follow the stack depth (an indirect call whose callee
pops an unknown number of bytes, say), it says so rather than printing numbers it does not
believe.

## Step 2: the instructions

```
$ python tools/reimplementation-helper/batch/structural_diff.py aiGiveRaidInstructions
  instructions   original 241   ours 234   (-7)
  kind  0.960   <- drive this to 1.000 first; every difference here is real
  shape 0.939   <- operand form, once registers and constants are anonymised
  skel  0.939   <- the same instructions with only REGISTER NAMES anonymised
  raw   0.568   <- reccmp, mostly register and slot naming
  delta 9 instruction(s) of mismatched kind
```

Four numbers, each deliberately blind to more than the last:

* **`kind`** - just the instruction names, all operands thrown away. `mov`, `add`, `push`...
  A difference here is always real.
* **`shape`** - operands kept, but register names turned into `r` and numbers into `k`.
  Catches "we used a constant where the original used a register".
* **`skel`** - the full instruction, with *only* register names blanked. The gap between
  `skel` and `raw` is purely register naming.
* **`raw`** - what reccmp says.

**`delta` is the most useful number.** It counts instructions, not ratios: "we emit two `xor`
the original does not". Here it is 9, and we are 7 instructions short overall.

Then the per-instruction table:

```
  mnemonic original ours
  je       13       11        -2
  movsx    7        5         -2
  add      8        7         -1
  imul     8        7         -1
  lea      6        5         -1
  test     14       13        -1
  jne      15       16        +1
```

### The trap, and the detector that exists because of it

Read that table as seven separate missing instructions and you will hunt for seven things. It
is not seven things. Look at the shape of it: one missing `test`, one `je`, one `imul`, **two**
`movsx`, one `lea`, one `add`. That is one missing **copy** of a seven-instruction sequence.

I got this wrong the first time on `renderDebugDataAiInfo` - the table read `add -1, mov -1,
push -1` and I went looking for three unrelated problems. So the tool now counts how many times
each sequence occurs on each side, and says it outright:

```
  DUPLICATION: the original computes this run 2 time(s), we compute it 1:
      test r, r
      je L
      imul r, r, 0x32c
      movsx r, word ptr [r + G]
      movsx r, word ptr [r + G]
      lea r, [r + r*0x2]
      add r, dword ptr [r*0x4 + G]
```

Register names are blanked first, so two copies still count as "the same sequence" even when
the compiler put them in different registers.

Translating that back to C++: `imul r, r, 0x32c` is multiplying by 812, which is the size of a
building record, so this is `buildings[something]`; the two `movsx` are reading two 16-bit
fields; `lea r, [r + r*2]` multiplies by 3. It is this line of our source:

```cpp
tile = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX
    + DAT_ViewportRenderState::instance
          .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY]
          .addXgetTile;
```

which appears three times in the function, once in each branch of an `if`/`else if`/`else`.

### Why "share less" is the fix, not "share more"

Your instinct is that duplicated code is bad and sharing is good. For matching, that instinct
is backwards: we have to produce whatever the original produced, and here the original
duplicates.

MSVC hoists a common expression out of both arms of an `if`/`else`, and - this is the key part
- it hoists **as much of the expression as is common**. On `renderDebugDataAiInfo` the original
did this:

```
imul eax, eax, 0x6d98                   ; shared, before the branch
cmp  dword ptr [esi - 0xdf4], 0
jne  arm_b
mov  eax, dword ptr [eax + 0x1866ac0]   ; arm A: duplicated
add  eax, 1
...
arm_b:
mov  edx, dword ptr [eax + 0x1866ac0]   ; arm B: the SAME load again
add  edx, 1
```

Only the multiply is shared; the identical load is duplicated. Four source versions were tried
and every one of them hoisted the whole thing:

| what we wrote | result |
| --- | --- |
| the full expression written out in both arms | whole chain hoisted |
| one shared local before the `if` | hoisted, obviously |
| a local declared before, assigned inside each arm | still hoisted |
| a ternary picking the format string | still hoisted |

The reason is the *extent* of what is common. Written out twice, the entire chain is common -
read the member, multiply, read the field, add one - so all of it gets hoisted. The original
shares only the **front** of that chain. So the source has to share exactly that front and
write the rest out:

```cpp
int aivID = DAT_GameState::instance.playerDataArray[playerID].aivID;   // share the index
if (...) sprintf(text, "AIV:n/a", DAT_AIVState::instance.aivs[aivID].castleID + 1);
else     sprintf(text, "AIV: %d", DAT_AIVState::instance.aivs[aivID].castleID + 1);
```

The index is shared because *we* shared it; the two reads are left alone because the compiler no
longer sees them as part of one common expression. `delta` went to 0 and the score went
**67.5% -> 83.6%**.

Sharing *more* than the original also costs you. Using a pointer to the element instead of the
index got within one instruction, because a pointer has to be fully computed (`base + index *
size`, an extra `add`), whereas the original keeps only `index * size` in a register and folds
the base into each read:

| form | delta | instructions |
| --- | --- | --- |
| expression inline in both arms | 5 | 300 |
| shared local before the branch | 3 | 302 |
| pointer/reference to the element | 1 | 306 |
| **index in a local** | **0** | **305** (matches) |

**The rule: share in the source exactly the prefix the original shares, and write the rest
out.**

## Step 3: registers - usually not your problem

```
  registers: 70 operand(s) differ only in which register was used.
  substitution   count
  ebp  -> ebx       27
  ebx  -> ebp       19
  ecx  -> edx        9

  The dominant substitution is a permutation in 2 closed cycle(s), covering
  66 of 70 (94%): eax -> ecx -> edx -> eax, ebp -> ebx -> ebp
```

When the substitutions form **closed cycles** like that, it means the allocation is structurally
right and the registers were just handed out in a different order - not that anything is broken.

The tool then tells you whether to care:

```
  The first STRUCTURAL difference is at original instruction 1 and the first
  REGISTER difference at 2, so the registers diverge at or after the structure
  does. ... these register names are an effect of that structural defect -
  fix it and they follow.
```

That is the useful verdict. If registers start differing *after* the instructions start
differing, they are a symptom. Fix step 2 and they sort themselves out - on
`renderDebugDataAiInfo`, once the instruction stream matched exactly, the register
substitutions dropped to **zero** with no register work at all.

If you ever do need to look at registers, `reg_scores.py` reads the decisions out of the
compiler itself with a debugger:

```
$ python tools/compiler-internals/reg_scores.py FILE.cpp --whyreg this
candidate              got   eax     ecx     edx     ebx     esp     ebp     esi     edi
tile                   eax   [0]     0       0       0       0       0       0       0
this                   ebp   12      -15     0       0       0       [6300]  0       0
```

Each row is one value, `got` is the register it received, and the numbers are what each register
"cost" - lowest wins, brackets mark the winner. Candidates are served in score order and take
the cheapest register still available, so what matters is **who gets served first**. Nothing
about variable names or types enters into it; the inputs are the instruction stream and which
registers are still busy.

## Where `aiGiveRaidInstructions` currently stands

Being honest about an unfinished one, because the dead ends are informative.

Known: the frame is **perfect** (step 1 done). `delta` is 9, of which 7 instructions are that
one missing copy of the tile computation. The registers are a clean two-cycle swap: the original
keeps `this` in `ebx` and `playerID * 0x39f4` (the player-record base) in `ebp`; we have them
the other way round.

Tried and rejected: moving `i` into the `for` initialiser. It cut `delta` from 9 to 3 - it
actually fixed the missing duplicate - but the score fell from **56.8% to 44.1%**, because it
scrambled the register assignment far more than it gained. Reverted.

Why the register swap resists: `ebx` comes before `ebp` in the compiler's preference list, so
whichever value is served first takes `ebx`. `reg_scores.py` shows our player-base temporary
scoring **82** against `this` at **60**, so the temporary is served first and takes `ebx`. In
the original, `this` won `ebx`. Those scores are weighted reference counts, and both sides use
these two values exactly 27 and 22 times - identical. So there is no expression to rewrite to
change the ranking, and no source change I can name that flips it. That is where it sits.

The lesson is the one from the table at the top: `delta` and the percentage can disagree, and
when they do, neither one alone is the answer. `delta` is the right target while the frame or
the instruction mix is still wrong, because those are *causes*. Once they are right, the
percentage is all that is left to steer by.

## Cheat sheet

```bash
# 1. the stack frame - do we have the right local variables?
python tools/reimplementation-helper/batch/slot_map.py src/.../Thing.cpp

# 2. the instructions - right ones, right order? read `delta` and any DUPLICATION block
python tools/reimplementation-helper/batch/structural_diff.py Thing

# rank every function in the build list by how reachable its problem is
python tools/reimplementation-helper/batch/structural_diff.py --all

# see the original's real machine code, whole function, correct ends
python tools/reimplementation-helper/batch/orig_body.py src/.../Thing.cpp

# a fast register-sensitive score - a compile, not a build, so seconds per try
python tools/reimplementation-helper/batch/quick_diff.py src/.../Thing.cpp -q

# 4. the official number, last
python tools/reimplementation-helper/batch/build_quiet.py
python tools/reimplementation-helper/batch/reccmp_report.py --run pct
```

Two traps worth repeating:

* **Do not read instruction streams out of `reccmp/dll/diff.json`.** It stores only the diff
  *view*, so the better a function matches the less of it is in there - a function at 99.7%
  leaves 22 lines behind out of 322 instructions. `structural_diff.py` used to read it and its
  numbers for good functions were meaningless. Both streams now come from the code itself.
* **A dropping percentage does not mean the change was wrong.** Check the frame and `delta`
  first. The one worked example here got better three times while the score went down once.

## When several functions stop on the same number, stop looking at the functions

Everything above hunts for a defect *inside* one function. Some defects are not in any
function, and they have a signature you can spot in the `pct` table in a second: several
unrelated functions sitting on **exactly** the same percentage.

`Text/FontSizeClass` looked like this:

```
 92.6  96.0 getWidthOfWideText
 95.6  96.0 renderMultilineWideTextUnk
 99.0  96.0 renderSomeSpecificTextUnk
 94.3  96.0 renderWideText
```

Four functions of very different sizes, all at 96.0 normalized. Running `structural_diff.py`
on each one said the same thing four times - `delta 0`, same instructions in the same order,
`kind 1.000`. That combination is the tell: **structurally perfect, yet not 100, and tied with
its neighbours.** No amount of rewriting the C++ can move a function that is already emitting
the right instructions in the right order.

So go straight to `reccmp_report.py diff` on the *smallest* of the group, because whatever is
shared will be a larger fraction of it and easier to see. Here the first line of the diff was
the whole answer: our `/GS` prologue read `__security_cookie` from our own `.data`, the
original read it from 0x00B94220. The fix was one new file in `src/symbols/`, it was worth 4%
in *every* `/GS`-protected function in the project, and no amount of staring at
`getWidthOfWideText`'s source would ever have found it, because its source was already right.

The general rule: `delta 0` plus a percentage below 100 means the cause is outside the
function - the build, the headers, a resolver, a calling convention. A tie across unrelated
functions tells you how far outside.
