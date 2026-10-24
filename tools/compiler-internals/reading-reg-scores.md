# Reading `reg_scores.py` output, from scratch

No compiler background assumed. If you know what a variable is and what a CPU register is, that's enough.

## The problem in one paragraph

A CPU can only do arithmetic on values that live in **registers**, and an x86 CPU from this era has seven
usable ones: `eax`, `ecx`, `edx`, `ebx`, `ebp`, `esi`, `edi`. Your function probably has more variables than
that, so the compiler has to decide which variables get a register and which get parked in memory (on the
stack). We are trying to make our C++ compile to the *exact same bytes* as the original game, so when the
original put `playerID` in `ebp` and ours puts it in `edx`, the bytes differ and the match percentage drops -
even though both programs behave identically. `reg_scores.py` reads the compiler's own decision-making to show
why that happened.

## How the compiler decides (the three ideas you need)

**1. Benefit.** Each variable gets a score for how much it would gain from a register. It is roughly "how many
times is this used", with uses inside a loop counting more because they run more often. More uses, higher
benefit. In `sellExcessGoods`, `amount` is written in eight different branches and then read, so it scores 70;
`playerID` scores 4.

**2. Order.** The compiler sorts the variables by benefit, highest first, and hands out registers in that
order. The top variable gets first pick. This is why benefit matters: it decides who chooses first.

**3. Cost.** When it is a variable's turn, the compiler doesn't just grab any free register. It builds a price
list - a cost for each of the seven registers - and takes the **cheapest** one. Prices come from:

* **A neighbour that is stuck.** If some other variable that is alive at the same time has only *one* register
  left that it could legally use, then stealing that register would force the neighbour out to memory. So that
  register gets charged `neighbour's benefit x 100`. This is where the big numbers come from, and why a single
  awkward variable can make one register expensive for everybody.
* **Affinity (a discount).** If a variable is already in a particular register for some other reason - it
  arrived as a parameter there, or a function returns its value in `eax`, or it is the `this` pointer which
  always arrives in `ecx` - then that register is *cheaper* for it. Affinity shows as a negative number.
* **Ties.** If several registers cost the same, the compiler uses a fixed preference list:
  `eax, ecx, edx, esi, edi, ebx, ebp`.

## Reading the actual output

### `--advise` / `--invocation`: the benefit list

```
candidate                    first    all rounds
amount                       70       +70
variance                     22       +22
playerID                     4        +4
```

Highest first. The ones near the top get registers; the ones near the bottom usually end up in memory. "All
rounds" shows the same variable re-scored several times, because the compiler takes multiple passes and
recalculates between them.

### `--whyreg`: the price list for each decision

```
candidate   got   eax    ecx    edx    ebx    esp   ebp   esi    edi
this        ecx   0      [-1]   1      0      0     0     0      0
playerID    edx   0      0      [-1]   0      0     0     1200   0
```

One row per decision. `got` is the register it ended up with, and the **bracketed** number is that register's
price. Read the first row as: "`this` took `ecx`, which cost -1 - a discount, because `this` always arrives in
`ecx`." Second row: "`playerID` took `edx` at -1; `esi` would have cost 1200, so `esi` was effectively off the
table."

To move a variable to a different register, that register's price has to drop below the bracketed one. That is
the whole counterfactual, and it is just arithmetic.

### `--whycost`: who set those prices

```
playerID -> ebx
    ebx   total  +13800   PIN +800 by (temp); PIN +300 by (temp)
(temp) -> edx
    ebp   total   +4700   PIN +1400 by behaviourType; PIN +1000 by i
```

`PIN` means "a stuck neighbour charged this". The second block is the useful kind: **`ebp` is expensive for
everyone because the variables `behaviourType` and `i` are stuck on it**, charging 1400 and 1000. Those are
names from our source code, so they are things a person could act on.

`(temp)` means the charge came from a value the compiler invented itself - an intermediate result with no name
in our code. You cannot act on those, because there is no line of source to change. **The whole point of
`--whycost` is telling those two cases apart.**

An empty table means nothing was charged at all: every register was free, the prices were all zero, and the
tie-break list alone decided. That function cannot be steered from the source, so stop working on it.

## The catch, which is important

Benefit counts *uses*. Cost comes from *which variables are alive at the same time* and from *where values
cross function-call boundaries*. All of those are facts about **what the code does**, not about how it is
typed. Renaming a variable, moving its declaration, or reordering statements does not change any of them -
which is why those tricks never move a register assignment, and why a tool cannot just rewrite your syntax to
fix a mismatch.

There is also a trap worth knowing. "This variable is stuck on `ebp` and charging 1400, so I will give it a
shorter life" sounds right and is wrong: a shorter life with the same number of uses means *more uses per unit
of life*, so the benefit goes **up**, so the charge goes **up**. Measured on `aiRecruitUnits`: moving
`behaviourType`'s declaration inside the loop raised its charge from 1400 to 1600 and the match fell from 50.0%
to 48.9%.

So treat the output as an explanation, not an instruction. It reliably tells you *why* a register went where it
did, and it reliably tells you when to **give up on a function** - which saves real time. Turning it into a fix
means restructuring what the function computes, and every edit has to be measured with
`reccmp_report.py --run` afterwards, because the price list changes the moment you touch anything.
