"""Cases for unmod.py.

usage:
  test_unmod.py
"""

import unmod

PLAIN = """            uint v = x & 0x8000000f;
            if ((int)v < 0) {
                v = (v - 1 | 0xfffffff0) + 1;
            }
"""
SUM = """            uVar9 = (int)a->b + 4U & 0x80000007;
            if ((int)uVar9 < 0) {
                uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
            }
"""
FIELD = """                this->u[i].r = this->u[i].fixedRng & 0x80000003;
                if ((int)this->u[i].r < 0) {
                    this->u[i].r = (this->u[i].r - 1 | 0xfffffffc) + 1;
                }
"""
# the repair constant does not complement the mask: not this idiom
BAD_COMP = """            uint v = x & 0x8000000f;
            if ((int)v < 0) {
                v = (v - 1 | 0xfffffff8) + 1;
            }
"""
# the repair is applied to a different variable
BAD_VAR = """            uint v = x & 0x8000000f;
            if ((int)w < 0) {
                w = (w - 1 | 0xfffffff0) + 1;
            }
"""
# a bare mask, with no repair, is not a signed modulo
BARE = "            uint v = x & 0xf;\n"

CASES = [
    # the dividend gets a signed cast: the repair the compiler emitted only exists for a
    # signed operand, so an unsigned `%` would compile to a bare `and` and stop matching
    (PLAIN, "            uint v = (int)x % 16;\n", 1),
    (SUM, "            uVar9 = ((int)a->b + 4) % 8;\n", 1),
    (FIELD, "                this->u[i].r = (int)this->u[i].fixedRng % 4;\n", 1),
    (BAD_COMP, BAD_COMP, 0),
    (BAD_VAR, BAD_VAR, 0),
    (BARE, BARE, 0),
]

if __name__ == "__main__":
    failures = 0
    for src, want, want_n in CASES:
        got, n = unmod.process(src)
        ok = got == want and n == want_n
        failures += not ok
        print("%-4s %s" % ("ok" if ok else "FAIL", src.strip().split("\n")[0]))
        if not ok:
            print("       got  %r (%d)\n       want %r (%d)" % (got, n, want, want_n))
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
