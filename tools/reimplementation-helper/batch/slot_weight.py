"""Explain an `[esp + N]` layout through the weight the stack colorer actually sorts on.

usage: slot_weight.py FILE.cpp [--reorder] [--quiet]

MSVC 14.00 does not lay spilled locals out in declaration order. `ColorStackElements`
(`P2/stack.c`) builds one 28-byte record per stack element, holding the local's size
rounded up to 4 and its accumulated reference weight, sorts the records with
`StkColorCmp` on `(class, weight * 1000 / size)` and then hands out offsets in that
order. So for a block of same-sized locals the layout is simply **descending reference
weight**, and the lever on it is how often - and at what loop depth - the source reads
each local, not where it is declared. See IMPLEMENTATION_CHEAT_SHEET.md, "Variable Usage".

This script makes that visible for one function:

* it compiles the file with `/FA` and reads the `_name$ = N` table MSVC emits, which is
  the ground truth for which local got which slot - no guessing from the diff;
* it counts the references to each local in the source, weighting a reference inside a
  loop by 10 per nesting level as a proxy for block frequency;
* it reports whether the slots come out monotone in that weight. A violation means the
  proxy is wrong for this function (an unequal size, a differing class, or a loop the
  brace heuristic misreads), not that the model is wrong - read the report, do not
  trust the suggestion blindly;
* with a reccmp run available it prints the original's slot census beside ours and names
  the first position where the two disagree, which is the local whose reference count has
  to change.

`--reorder` rewrites the leading run of initialised same-type declarations into descending
weight order. That cannot move a local between weight classes, so it only decides **ties**,
which `StkColorCmp` leaves to the order the symbols arrive in, permuted by an unstable
quicksort (`QSortColors`). Treat it as one cheap variant to measure, not as a repair:
re-run `reccmp_report.py --run` afterwards and revert it if it does not pay.

Renaming locals does nothing - `allowQuarries` -> `zzz` and `allowWoodcutters` ->
`aaaaaaaaaa` left `planToBuyWhenLowOnResourceAndSnoozeBuildings` byte-identical. The
comparator never looks at a name.
"""

import json
import os
import re
import subprocess
import sys

import common

REORDER = "--reorder" in sys.argv
QUIET = "--quiet" in sys.argv
files = [a for a in sys.argv[1:] if not a.startswith("-")]
if not files:
    sys.exit(__doc__)

# absolute: the compile runs with the build directory as its cwd, so a relative /Fo would miss
OUT = (common.ROOT / common.TMP / "slotweight").resolve()
OUT.mkdir(parents=True, exist_ok=True)

SLOT_RE = re.compile(r"^(\w+\$\w*|tv\d+) = (-?\d+)", re.M)
DECL_RE = re.compile(r"^(\s*)((?:unsigned |signed |const )*\w[\w:]*)\s+(\w+)\s*=\s*([^;]+);\s*$")
LOOP_RE = re.compile(r"^\s*(for|while|do)\b")


def compile_fa(path):
    """Compile one file with /FA and return the listing text."""
    cc = json.loads(common.read_text(common.BUILD_DIR / "compile_commands.json"))
    ours = [
        e
        for e in cc
        if "OpenSHC.dll.dir" in e["command"] and "/src/OpenSHC/" in e["file"].replace("\\", "/")
    ]
    if not ours:
        sys.exit("no OpenSHC.dll compile command in compile_commands.json - configure the build first")
    cmd = ours[0]["command"]
    out = str(OUT).replace("\\", "/")
    # lambda replacements: a Windows path in the replacement string would be read as escapes
    cmd = re.sub(r"/Fo\S+", lambda _m: "/Fo%s/w.obj /FA /Fa%s/w.asm" % (out, out), cmd)
    cmd = re.sub(r"-c \S+$", lambda _m: "-c " + str(path), cmd)
    env = common.build_env()
    # cl.exe loads its own DLLs from Common7/IDE, as quick_diff.py does for the same reason
    env["PATH"] = str(common.ROOT / "MSVC1400-SP1" / "Common7" / "IDE") + os.pathsep + env["PATH"]
    r = subprocess.run(cmd, cwd=ours[0]["directory"], env=env, capture_output=True, text=True)
    if r.returncode:
        out = (r.stdout or "") + (r.stderr or "")
        print("compile failed (%d):" % r.returncode)
        print("\n".join(l for l in out.splitlines() if "error" in l) or out[-800:] or "(no diagnostics)")
        return None
    return common.read_text(OUT / "w.asm")


def our_slots(listing, cls, name):
    """{local: frame offset} for one function, from MSVC's own symbol table."""
    m = re.search(r"^(\?%s@%s@\S+) PROC" % (re.escape(name), re.escape(cls)), listing, re.M)
    if not m:
        return None
    pre = listing[listing.rfind("_TEXT\tSEGMENT", 0, m.start()) : m.start()]
    out = {}
    for sym, off in SLOT_RE.findall(pre):
        if sym.startswith("tv"):
            continue
        # MSVC prefixes a local with exactly one underscore; sources here often start with
        # one of their own (`_textLength` -> `__textLength$`), so strip only the first.
        out[re.sub(r"\$\d*$", "", re.sub(r"^_", "", sym))] = int(off)
    return out


def weights(body, names):
    """Reference count per local, a reference inside N *loops* counted 10**N times."""
    raw = dict.fromkeys(names, 0)
    weighted = dict.fromkeys(names, 0)
    braces, loop_stack = 0, []
    for line in body.split("\n"):
        starts_loop = LOOP_RE.match(line) is not None
        for n in names:
            hits = len(re.findall(r"\b%s\b" % re.escape(n), line))
            if hits:
                raw[n] += hits
                weighted[n] += hits * 10 ** len(loop_stack)
        braces += line.count("{") - line.count("}")
        braces = max(braces, 0)
        # a loop body is the brace level opened on (or just after) the loop header
        if starts_loop:
            loop_stack.append(braces)
        while loop_stack and braces < loop_stack[-1]:
            loop_stack.pop()
    return raw, weighted


def signature_params(text, cls, name):
    """Names of the incoming parameters, which are ABI-placed and never colored."""
    m = re.search(
        r"FUNCTION: STRONGHOLDCRUSADER[^\n]*\n\s*[\w:*&<> ]*?%s::%s\s*\(([^{]*?)\)\s*\n?\s*\{"
        % (re.escape(cls), re.escape(name)),
        text,
        re.S,
    )
    if not m:
        return set()
    out = set()
    for part in m.group(1).split(","):
        ids = re.findall(r"\b(\w+)\b", part)
        if ids:
            out.add(ids[-1])
    return out


def decl_block(text):
    """The longest run of consecutive initialised declarations in the body."""
    lines = text.split("\n")
    best, cur = [], []
    for i, line in enumerate(lines):
        if DECL_RE.match(line):
            cur.append(i)
        else:
            if len(cur) > len(best):
                best = cur
            cur = []
    return best if len(best) > len(cur) else cur


def report(path):
    text = common.read_text(path)
    m = re.search(r"FUNCTION: STRONGHOLDCRUSADER[^\n]*\n[^\n(]*?(\w+)::(\w+)\(", text)
    if not m:
        print("%s: no `// FUNCTION:` marker followed by a definition" % path)
        return
    cls, name = m.groups()
    listing = compile_fa(path)
    if listing is None:
        return
    slots = our_slots(listing, cls, name)
    if not slots:
        print("%s: no code emitted for %s::%s (inlined, or the listing names it differently)" % (path, cls, name))
        return

    names = [mm.group(3) for mm in (DECL_RE.match(l) for l in text.split("\n")) if mm]
    names += [n for n in slots if n not in names]
    raw, wt = weights(text, names)

    params = signature_params(text, cls, name)
    shared = {}
    for n, o in slots.items():
        if n not in params:
            shared.setdefault(o, []).append(n)
    print("### %s::%s" % (cls, name))
    print("%-28s %6s %8s %6s %10s %8s" % ("local", "refs", "wrefs", "size", "wrefs/byte", "slot"))
    slot_weight = {o: sum(wt.get(x, 0) for x in ns) for o, ns in shared.items()}
    # StkColorCmp divides by the element's size, so recover each size from the gap to the
    # next slot: a local wider than 4 bytes legitimately sorts below a lighter narrow one.
    negative = sorted(o for o in shared if o <= 0)
    size = {}
    for i, o in enumerate(negative):
        size[o] = (negative[i + 1] - o) if i + 1 < len(negative) else 4
    density = {o: (slot_weight[o] * 1000) // max(size.get(o, 4), 1) for o in negative}
    ordered = sorted((o, n) for n, o in slots.items())
    prev, violations, reused = None, [], []
    seen = set()
    for off, n in ordered:
        if n in params:
            # incoming parameters are placed by the calling convention, not by the colorer
            print("%-28s %6d %8d %6s %10s %8d   (parameter, not colored)"
                  % (n, raw.get(n, 0), wt.get(n, 0), "-", "-", off))
            continue
        mark = ""
        if off > 0:
            reused.append(n)
            mark = "  <- positive offset: reuses a dead parameter's slot"
        elif off not in seen and prev is not None and density.get(off, 0) > prev:
            mark = "  <- heavier than the slot below it"
            violations.append(n)
        if off <= 0 and off not in seen:
            prev = density.get(off, 0)
            seen.add(off)
        print("%-28s %6d %8d %6s %10s %8d%s"
              % (n, raw.get(n, 0), wt.get(n, 0),
                 size.get(off, "-"), density.get(off, "-"), off, mark))

    multi = {o: ns for o, ns in shared.items() if len(ns) > 1}
    if multi:
        print("")
        for o, ns in sorted(multi.items()):
            print("slot %d is shared by %d locals (%s)" % (o, len(ns), ", ".join(sorted(ns))))
        print("Disjoint live ranges share one slot, so a slot count is not a local count.")
    if any(o > 0 for o in shared):
        print("")
        print("A local at a positive offset reuses the slot of a parameter already dead. This is")
        print("where Ghidra's \"repurposed parameter\" rendering comes from: the compiler did it,")
        print("the original source did not - do not transcribe it back.")
    if violations:
        print("\nweight per byte is NOT monotone here (%s)." % ", ".join(violations))
        print("Expected when the locals are not one homogeneous class: `StkColorCmp` keys on a")
        print("class byte first, and arrays or address-taken locals sort in their own group. It")
        print("can also mean the 10x-per-loop proxy misreads this control flow. Use the numbers")
        print("as a hint about which local is light or heavy, not as a layout prediction.")
    elif not QUIET:
        print("\nslots are monotone in weight per byte, as the colorer's comparator implies.")

    compare_original(name, slots, wt)

    if REORDER:
        do_reorder(path, text, wt)


def compare_original(name, slots, wt):
    """Put the original's slot census beside ours and name the first disagreement."""
    try:
        byaddr = common.load_diff()
    except Exception:
        return
    esp = re.compile(r"\[esp \+ (0x[0-9a-f]+)\]")
    for _f, e, _a in common.entries(byaddr):
        if e is None or not e.get("diff") or not e["name"].endswith("::" + name):
            continue
        orig, ours = common._asm_lines(e)
        census = []
        for stream in (orig, ours):
            c = {}
            for line in stream:
                for mm in esp.finditer(line):
                    v = int(mm.group(1), 16)
                    c[v] = c.get(v, 0) + 1
            census.append(c)
        o, u = census
        print("\n  original %2d slots: %s" % (len(o), " ".join("%#x:%d" % kv for kv in sorted(o.items()))))
        print("  ours     %2d slots: %s" % (len(u), " ".join("%#x:%d" % kv for kv in sorted(u.items()))))
        if len(o) != len(u):
            print("  %+d colored stack elements: a local one side spills and the other enregisters," % (len(u) - len(o)))
            print("  which is a live-range difference, not a declaration-order one.")
        ol = [c for _, c in sorted(o.items())]
        ul = [c for _, c in sorted(u.items())]
        for i, (a, b) in enumerate(zip(ol, ul)):
            if a != b:
                print("  first differing position: slot #%d, original touched %d times, ours %d." % (i, a, b))
                print("  Under the weight model that position holds locals of different weight;")
                print("  look for a read the original has and we do not (or the reverse).")
                break
        return


def do_reorder(path, text, wt):
    lines = text.split("\n")
    idx = decl_block(text)
    if len(idx) < 2:
        print("\n--reorder: no run of initialised declarations to permute.")
        return
    block = [lines[i] for i in idx]
    decls = [DECL_RE.match(l) for l in block]
    types = set(d.group(2) for d in decls)
    if len(types) != 1:
        print("\n--reorder: the run mixes types (%s); refusing, sizes differ and so does the key." % ", ".join(sorted(types)))
        return
    order = sorted(range(len(block)), key=lambda k: -wt.get(decls[k].group(3), 0))
    if order == list(range(len(block))):
        print("\n--reorder: declarations are already in descending weight order.")
        return
    for pos, src in zip(idx, order):
        lines[pos] = block[src]
    common.write_text(path, "\n".join(lines))
    common.format_file(path)
    print("\n--reorder: rewrote %d declarations into descending weight order." % len(idx))
    print("This only decides ties. Re-measure with reccmp_report.py --run and revert if it does not pay.")


for f in files:
    report(os.path.abspath(f))
