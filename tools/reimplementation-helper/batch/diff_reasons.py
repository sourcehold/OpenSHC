"""Report where each function's assembly first really diverges from the original.

A reccmp diff cascades: one differing instruction pushes everything after it out of step,
so the size of a diff says little about how much is actually wrong. What is worth acting on
is the *first* divergence that is not just a register choice, and the source line it is
attributed to. That is what this prints, one line (plus context) per function.

    python diff_reasons.py                    # every file in the sources list
    python diff_reasons.py --context 6        # more instructions around the divergence
    python diff_reasons.py UpdateChild

Ordering is by source line, so the earliest divergence in each file comes first; fix that,
rebuild, and the next one appears. Differences that are only register names or only a call
target are skipped, since the source cannot address those (see the batch README).

Needs a current reccmp/dll/diff.json (reccmp_report.py --run ...).
"""

import re
import sys

import common
import compare_constants

REGISTERS = r"(?:e?(?:ax|bx|cx|dx|si|di|bp|sp)|[abcd][lh])"


def canonical(text):
    """The instruction with register names, call targets and absolute addresses removed."""
    s = text.split("\t")[0].strip()
    s = re.sub(r"<OFFSET\d+>|trampoline<[^>]*>|FunctionResolver::\S+", "T", s)
    s = re.sub(r"<[^>]*>", "<T>", s)
    s = re.sub(r"0x[0-9a-f]{5,}", "A", s)
    s = re.sub(r"\b%s\b" % REGISTERS, "r", s)
    return s


# housekeeping the register allocator places freely: a difference made only of these says
# nothing about the source
NOISE = re.compile(r"^(push r|pop r|mov r, r|mov r, dword ptr \[A\]|imul r, r, A|"
                   r"mov r, dword ptr \[StructResolver::Instance<T>::instance \(DATA\)\]|lea r, \[r\]|"
                   r"mov r, \d+|xor r, r|add r, r|sub r, r|nop.*|mov r, A)$")


def housekeeping_only(original, ours):
    return all(NOISE.match(canonical(x)) for x in original + ours)


def rows(entry):
    """The diff as (kind, instruction, source line) triples, in order."""
    out = []
    line = None
    for hunk in entry.get("diff") or []:
        for block in hunk[1]:
            for kind, items in block.items():
                for item in items:
                    parts = item[1].split("\t")
                    if kind != "orig" and len(parts) > 1:
                        m = re.search(r"\.cpp:(\d+)\)", parts[1])
                        if m:
                            line = int(m.group(1))
                    out.append((kind, parts[0].strip(), line))
    return out


def first_divergence(entry):
    """(source line, original instructions, our instructions) at the first real difference."""
    pending_original, pending_ours, line = [], [], None
    for kind, text, at in rows(entry):
        if kind == "both":
            if pending_original or pending_ours:
                # a run of replaced instructions ended; is any of it more than registers?
                if ([canonical(x) for x in pending_original] != [canonical(x) for x in pending_ours]
                        and not housekeeping_only(pending_original, pending_ours)):
                    return line, pending_original, pending_ours
            pending_original, pending_ours, line = [], [], None
            continue
        if kind == "orig":
            pending_original.append(text)
        else:
            pending_ours.append(text)
            line = line or at
    if pending_original or pending_ours:
        if ([canonical(x) for x in pending_original] != [canonical(x) for x in pending_ours]
                and not housekeeping_only(pending_original, pending_ours)):
            return line, pending_original, pending_ours
    return None, [], []


def reason(original, ours):
    """A short guess at what kind of difference this is."""
    co, cu = [canonical(x) for x in original], [canonical(x) for x in ours]
    if sorted(co) == sorted(cu):
        return "instruction scheduling"
    if all(x.startswith(("call", "jmp T")) for x in co + cu):
        return "call target"
    if len(co) != len(cu):
        return "different number of instructions"
    return "different instructions"


def main():
    argv = sys.argv[1:]
    context = 3
    if "--context" in argv:
        i = argv.index("--context")
        context = int(argv[i + 1])
        del argv[i:i + 2]
    names = [a for a in argv if not a.startswith("--")]
    byaddr = common.load_diff()
    found = []
    for path, entry, _ in common.entries(byaddr, compare_constants.select(names)):
        if entry is None:
            continue
        line, original, ours = first_divergence(entry)
        if line is None and not original and not ours:
            found.append((0, path, entry, None, [], []))
        else:
            found.append((line or 0, path, entry, line, original, ours))
    found.sort(key=lambda r: (r[3] is None, r[0]))
    for _, path, entry, line, original, ours in found:
        name = entry["name"].split("::")[-1]
        if line is None and not original:
            print("%-26s %5.1f%% norm %5.1f%%  nothing but registers, calls and prologue housekeeping" % (
                name, float(entry["matching"]) * 100, common.normalized_ratio(entry) * 100))
            continue
        print("%-26s %5.1f%% norm %5.1f%%  first divergence at %s:%s -- %s" % (
            name, float(entry["matching"]) * 100, common.normalized_ratio(entry) * 100,
            path.split("/")[-1], line, reason(original, ours)))
        for text in original[:context]:
            print("      orig  " + text)
        for text in ours[:context]:
            print("      ours  " + text)


if __name__ == "__main__":
    main()
