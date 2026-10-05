"""Find differences that point at a wrong type, addressing mode or constant, per function in
cmake/openshc-sources.txt.local.

usage: diff_types.py [--run] [NAME-SUBSTRING]

`diff_jcc.py` covers comparisons and `diff_triage.py` covers frames and slots; this covers the three
remaining classes that have a source-level fix:

  EXTEND    `movsx` on one side and `movzx` on the other for the same operand. The field's
            signedness is wrong in the generated header: `char` vs `byte`, `short` vs `ushort`.
            Commit header retypes separately from the .cpp work.
  SIGNFLIP  `add` against `sub` of the same magnitude on the same destination: a sign error in a
            formula. Trust the asm over the decompilation - Ghidra rendered `2400 / n + 40` where the
            binary has `sub eax, 0x28`, so the formula was `- 40`, and the function reached 100% once
            corrected.
A third class, `this->` against the global instance, is deliberately not reported. One function often
reads some fields through `this` and others through `DAT_*::instance`, in both directions at once, so
counting anchored operands fires for almost every function and proves nothing about any single
access. Read it off `reccmp_report.py diff` instead: a `this`-relative operand on one side against a
`StructResolver::Instance<..>` symbol on the other, for the *same* field, is the signal. That needs
the global data reimplementations switched on (the `MACRO_STRUCT_RESOLVER` flag in
`src/OpenSHC/Globals/*.hpp`, never committed); with them off every absolute address looks alike.

Instructions are paired inside one reccmp replacement block and only when both sides have the same
number of that kind of line. Once the streams drift, the n-th instruction on each side is no longer
the same instruction, and pairing them invents differences that are not there. Confirm every hit
against `reccmp_report.py diff` before editing.

Both rules were checked in both directions: they fire on the two known bugs when those are
reintroduced (a `char` layer that should be `byte`, and `+ 40` that should be `- 40`) and report
nothing across the 101 functions of `Game::GameStateStructures` once fixed. A third rule, "same
instruction with a different constant", was tried and removed: every one of its hits on that folder
was a loop-induction stride (`imul reg, 0x39f4` against a different element size, `add reg, 4`
against `add reg, 0x14`), never a constant the source chose.

--run re-runs reccmp first (otherwise reccmp/dll/diff.json from the last run is used).
"""

import re
import sys

import common

IMM_RE = re.compile(r"(-?0x[0-9a-f]+|(?<![\w$])-?\d+)$")
THIS_RE = re.compile(r"\b(ecx|esi|edi|ebx|ebp) \+ 0x[0-9a-f]{4,}")


def op(line):
    return line.split("\t")[0].strip()


def scrub_regs(s):
    return re.sub(r"\b(e?[abcd]x|e?[sd]i|e?[sb]p|[abcd][lh])\b", "R", s)


def mem_shape(s):
    """Operand width plus the symbol or displacement, with base registers dropped.

    `movzx edx, byte ptr [esi + I<X>::instance+N]` and `movsx eax, byte ptr [ebx + esi + I<X>::instance+N]`
    reach the same array, so only the width and the symbol identify the access.
    """
    m = re.search(r"(byte|word|dword) ptr \[(.*)\]", s)
    if not m:
        return None
    inner = re.sub(r"\b(e?[abcd]x|e?[sd]i|e?[sb]p)\b(\*\d)?\s*\+?\s*", "", m.group(2))
    return m.group(1), inner.strip()


def blocks(entry):
    """[(orig_lines, recomp_lines)] per replacement block."""
    pairs = []
    for hunk in entry.get("diff") or []:
        for block in hunk[1]:
            o = [op(r[1]) for r in block.get("orig", [])]
            r = [op(r[1]) for r in block.get("recomp", [])]
            if o and r:
                pairs.append((o, r))
    return pairs


def hints_for(entry):
    pairs = blocks(entry)
    hits = []

    def add(cls, a, b):
        if (cls, a, b) not in hits and len(hits) < 25:
            hits.append((cls, a, b))

    def zip_kind(o, r, keep):
        a = [x for x in o if keep(x)]
        b = [x for x in r if keep(x)]
        return list(zip(a, b)) if len(a) == len(b) else []

    for o, r in pairs:
        # EXTEND: same width and same symbol/displacement, different extension. Base registers are
        # ignored on purpose - the two sides often reach the same array through different registers,
        # and requiring those to match was what made this miss real cases.
        for a, b in zip_kind(o, r, lambda x: x.startswith(("movsx ", "movzx "))):
            if a.split()[0] != b.split()[0] and mem_shape(a) == mem_shape(b):
                add("EXTEND", a, b)
        # SIGNFLIP: add against sub (or the reverse) on the same destination with the same magnitude.
        # This is what a wrong sign in a formula looks like; the constant itself is identical, so the
        # CONST rule below can never see it.
        for a, b in zip_kind(o, r, lambda x: x.startswith(("add ", "sub ")) and IMM_RE.search(x)):
            ma, mb = IMM_RE.search(a), IMM_RE.search(b)
            if (a.split()[0] != b.split()[0] and ma.group(1) == mb.group(1)
                    and scrub_regs(a[len(a.split()[0]):ma.start()])
                    == scrub_regs(b[len(b.split()[0]):mb.start()])):
                add("SIGNFLIP", a, b)
    return hits


def main():
    args = sys.argv[1:]
    if args and args[0] == "--run":
        common.run_reccmp()
        args = args[1:]
    want = args[0] if args else ""
    byaddr = common.load_diff()
    shown = total = 0
    for f, e, a in common.entries(byaddr):
        if e is None or float(e["matching"]) >= 1 or want not in e["name"]:
            continue
        total += 1
        hits = hints_for(e)
        if not hits:
            continue
        shown += 1
        print("### %s %.1f%% norm %.1f%%"
              % (e["name"], float(e["matching"]) * 100, common.normalized_ratio(e) * 100))
        for cls, x, y in hits:
            print("  %-8s orig: %-44s ours: %s" % (cls, x, y))
    if not total:
        print("nothing below 100% in the current list")
    else:
        print("\n%d of %d function(s) below 100%% have a type or sign hint" % (shown, total))


if __name__ == "__main__":
    main()
