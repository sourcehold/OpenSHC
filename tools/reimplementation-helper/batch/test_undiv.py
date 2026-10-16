"""Cases for undiv.py.

The rewrites here are the shapes actually found in the decompiled sources, plus the
near-misses that must be left alone: a mismatched shift, a mask that is not 2^k - 1, and a
bias taken from a different variable than the one being divided.

usage:
  test_undiv.py
"""

import undiv

CASES = [
    # the plain form
    ("v = (x + (x >> 0x1f & 7U)) >> 3;", "v = x / 8;"),
    # the sum wrapped in a signed cast, which is where the shift then sits
    ("v = (int)(x + (x >> 0x1f & 0xfU)) >> 4;", "v = x / 16;"),
    # a cast on the dividend inside the bias as well as outside it
    ("v = (int)((int)a->b + ((int)a->b >> 0x1f & 7U)) >> 3;", "v = a->b / 8;"),
    # a wide mask
    ("v = ((int)(r + ((int)r >> 0x1f & 0x1ffU)) >> 9) + k;", "v = (r / 512) + k;"),
    # two independent divisions in one expression
    ("v = ((x + (x >> 0x1f & 7U)) >> 3) - ((y + (y >> 0x1f & 7U)) >> 3);",
     "v = (x / 8) - (y / 8);"),
    # shift does not match the mask: not this idiom, leave it
    ("v = (x + (x >> 0x1f & 7U)) >> 2;", "v = (x + (x >> 0x1f & 7U)) >> 2;"),
    # mask is not 2^k - 1
    ("v = (x + (x >> 0x1f & 5U)) >> 3;", "v = (x + (x >> 0x1f & 5U)) >> 3;"),
    # the bias is taken from a different variable
    ("v = (x + (y >> 0x1f & 7U)) >> 3;", "v = (x + (y >> 0x1f & 7U)) >> 3;"),
    # an unbiased shift is an unsigned division or a real shift; not ours to touch
    ("v = x >> 3;", "v = x >> 3;"),
]

if __name__ == "__main__":
    failures = 0
    for src, want in CASES:
        got, _ = undiv.process(src)
        ok = got == want
        failures += not ok
        print("%-4s %s" % ("ok" if ok else "FAIL", src))
        if not ok:
            print("       got  %s\n       want %s" % (got, want))
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
