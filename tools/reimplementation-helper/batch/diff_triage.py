"""Decide where source work can still help, per function in cmake/openshc-sources.txt.local.

usage: diff_triage.py [--run] [path-filter]

Columns, all derived from the last reccmp run:

  pct     reccmp match %
  raw     difflib ratio over the two instruction streams
  norm    the same ratio after renaming registers to R, `[esp + 0xN]` to [SLOT]
          and literals to N
  frame   `sub esp, N` on each side
  byte    number of byte-sized `[esp]` accesses on each side
  ret     position of each `ret`, as a fraction of the stream

How to read it:

  norm >> raw           only register/stack-slot naming is left; stop editing
                        the source, the allocator is not reachable from it
  norm still low        real structure or ordering differs; keep looking
  frame differs         one local too many or too few - chase it with
                        diff_slots.py, this has been worth 10-30 points
  byte on our side only every bool/byte local is an int in the original
  ret positions differ  we inline a cold early-return block the original
                        outlines (or the reverse); restructure the guard so the
                        cold case is last in the source
"""

import re
import sys

import common

REG = re.compile(r"\b(e?[abcd]x|e?[sd]i|e?bp|e?sp|[abcd][lh])\b")
BYTE_SLOT = re.compile(r"(^|[^d])byte ptr \[esp")
FRAME = re.compile(r"^sub esp, (0x[0-9a-f]+|\d+)")

args = sys.argv[1:]
if args and args[0] == "--run":
    common.run_reccmp()
    args = args[1:]
path_filter = args[0] if args else ""


def normalize(line):
    s = line.split("\t")[0].strip()
    s = REG.sub("R", s)
    s = re.sub(r"\[R \+ 0x[0-9a-f]+\]", "[SLOT]", s)
    s = re.sub(r"0x[0-9a-f]+", "N", s)
    return re.sub(r"\b\d+\b", "N", s)


def frame_of(stream):
    for line in stream:
        m = FRAME.match(line.split("\t")[0].strip())
        if m:
            return m.group(1)
    return "-"


def ret_positions(stream):
    hits = [i for i, t in enumerate(stream) if t.split("\t")[0].strip().startswith("ret")]
    return [round(i / max(1, len(stream)), 2) for i in hits][:6]


import difflib  # noqa: E402  (after common, which chdirs to the repo root)

rows = []
for f, e, address in common.entries(common.load_diff()):
    if e is None or path_filter not in f or not e.get("diff"):
        continue
    orig, ours = common._asm_lines(e)
    raw = difflib.SequenceMatcher(None, orig, ours, autojunk=False).ratio()
    nrm = difflib.SequenceMatcher(None, [normalize(x) for x in orig],
                                  [normalize(x) for x in ours], autojunk=False).ratio()
    fo, fu = frame_of(orig), frame_of(ours)
    bo = sum(1 for t in orig if BYTE_SLOT.search(t))
    bu = sum(1 for t in ours if BYTE_SLOT.search(t))
    ro, ru = ret_positions(orig), ret_positions(ours)
    flags = []
    if fo != fu:
        flags.append("FRAME")
    if bu > bo:
        flags.append("BYTE")
    if ro != ru and (len(ro) != len(ru) or any(abs(a - b) > 0.08 for a, b in zip(ro, ru))):
        flags.append("RET")
    if not flags and nrm - raw > 0.25:
        flags.append("alloc-only")
    rows.append((float(e["matching"]), e["name"].split("::")[-1], raw, nrm, fo, fu, bo, bu, ro, ru, flags))

rows.sort()
print("%-38s %5s %6s %6s  %-6s %-6s %4s %4s  %s" %
      ("function", "pct", "raw", "norm", "frmO", "frmU", "byO", "byU", "flags"))
for m, name, raw, nrm, fo, fu, bo, bu, ro, ru, flags in rows:
    print("%-38s %5.1f %6.3f %6.3f  %-6s %-6s %4d %4d  %s" %
          (name, m * 100, raw, nrm, fo, fu, bo, bu, " ".join(flags)))
    if "RET" in flags:
        print("%-38s   orig ret %s   ours ret %s" % ("", ro, ru))
