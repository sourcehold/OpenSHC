"""Precedence tests for deparen.py.

Every case here is one where the brackets are load-bearing, or where an earlier version of
the script got it wrong. Run this after touching the precedence table.

usage:
  test_deparen.py
"""

import deparen

CASES = [
    # || inside && keeps its brackets (an earlier version dropped them and silently
    # changed the expression)
    ("(a != 0 || b != 0) && (x & 0x100) == 0",
     "(a != 0 || b != 0) && (x & 0x100) == 0"),
    # & binds looser than ==, so that group stays
    ("((x & 0x100) == 0 || (y & 0x100) == 0)",
     "(x & 0x100) == 0 || (y & 0x100) == 0"),
    # a plain over-bracketed && chain flattens
    ("(((a == 1) && (b == 2)) && (c == 3))", "a == 1 && b == 2 && c == 3"),
    # an assignment inside a condition keeps its group
    ("(a == 1) && ((v = f(x), v != 0))", "a == 1 && (v = f(x), v != 0)"),
    # && inside || is legal to unwrap but clearer kept
    ("(a == 1 && b == 2) || c == 3", "(a == 1 && b == 2) || c == 3"),
    # bitwise groups stay whatever joins them
    ("(a & 7) != 0 && (b | 1) == 3", "(a & 7) != 0 && (b | 1) == 3"),
    # a lone comparison unwraps
    ("(a == 1)", "a == 1"),
    # nested || of the same operator flattens
    ("((a == 1 || (b == 2)) || c == 3)", "a == 1 || b == 2 || c == 3"),
]

if __name__ == "__main__":
    failures = 0
    for src, want in CASES:
        outer = src
        while deparen.is_group(outer) and deparen.rank(outer[1:-1]) > 1:
            outer = outer[1:-1].strip()
        got = deparen.simplify(outer)
        ok = got == want
        failures += not ok
        print("%-4s %s" % ("ok" if ok else "FAIL", src))
        if not ok:
            print("       got  %s\n       want %s" % (got, want))
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
