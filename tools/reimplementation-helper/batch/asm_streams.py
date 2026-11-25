"""The two instruction streams for one function, both complete.

`reccmp/dll/diff.json` is **not** a source of whole functions, and anything that counts or
compares instructions must not read it. It stores the diff view - changed blocks plus a little
context - so the better a function matches, the less of it is there:

    aiCreateSiegeUnits   raw 0.997   diff.json: 22 lines per side   real function: 0x4fe bytes
    sellExcessGoods      raw 0.624   diff.json: 133 lines per side

A near-perfect function leaves a handful of lines behind, so counts taken from `diff.json` are
wrong in proportion to how good the code is - which is the worst possible direction for a tool
meant to rank functions by how much structural work they need.

Separately, the original side of `diff.json` is clipped: reccmp reads our function's byte length
from our PDB and dumps that many bytes from the original's address, so when our code is shorter
the original loses its tail. `aiGiveRaidInstructions` is cut 42 bytes early and appears to end
on `push edx; push eax` with no `ret` anywhere, when it plainly ends `004d2dfc ret 4`.

So both streams come from the code itself, which is what `quick_diff.py` already does:

* original - disassembled from `_original/Stronghold Crusader.exe` with capstone, the extent
  found by walking forward tracking the furthest forward branch target and stopping at the
  first `ret`/`jmp` at or past it. Nothing branches over the end of a function. Checked against
  Ghidra on three bodies - 004d1320/004d2000/004d2a70 - and exact on all three.
* ours - compiled with `/FA` and read out of the listing between `PROC` and `ENDP`.

Mnemonics are folded through `orig_body.canon`, because capstone says `jz` where MASM says `je`;
comparing unfolded invents differences that are not there.

`streams(path)` returns `(original, ours)` as normalised instruction lines, and `mnemonics()`
reduces either to a bare mnemonic list. `raw_entry()` is the one thing still worth taking from
`diff.json`: reccmp's percentage, for reference only.
"""

import os
import sys

import common
import orig_body

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
# `common` and `quick_diff` both chdir() to the repo root as they import, so a relative path
# from the command line must be resolved against `common.INVOCATION_DIR` - the cwd as it was -
# and not against os.getcwd(), which is already the root by the time anything here runs
import quick_diff   # noqa: E402  - imports cleanly; its CLI body is guarded by __main__


def resolve(path):
    """An absolute path, honouring the directory this process started in."""
    if os.path.isabs(path):
        return path
    for root in (str(common.INVOCATION_DIR), str(common.ROOT)):
        cand = os.path.join(root, path)
        if os.path.exists(cand):
            return os.path.abspath(cand)
    return os.path.abspath(os.path.join(str(common.INVOCATION_DIR), path))


def streams(path, keep_slots=False):
    """(original, ours) complete normalised instruction lines. `ours` is None if it failed."""
    quick_diff.keep_slots = keep_slots
    return quick_diff.streams(resolve(path))


def mnemonics(lines):
    """Bare canonical mnemonic sequence."""
    out = []
    for line in lines:
        parts = line.split()
        if not parts:
            continue
        m = parts[0].lower()
        if not m[0].isalpha() or m in orig_body.PADDING:
            continue
        out.append(orig_body.canon(m))
    return out


def raw_entry(path, byaddr=None):
    """reccmp's percentage for this file, or None - reference only, never for counting."""
    byaddr = byaddr if byaddr is not None else common.load_diff()
    for _f, e, _a in common.entries(byaddr, [path]):
        if e is not None:
            return e
    return None


if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    for p in sys.argv[1:]:
        o, u = streams(p)
        print('%-40s original %4d   ours %4d' % (os.path.basename(p), len(o), -1 if u is None else len(u)))
