"""Cases for unptr.py.

usage:
  test_unptr.py
"""

import unptr

CASES = [
    # the ordinary increment
    ("""            piVar1 = &this->units[i].attackedBy;
            *piVar1 = *piVar1 + 1;
""",
     "            this->units[i].attackedBy = this->units[i].attackedBy + 1;\n", 1),
    # a wrapped lvalue, which clang-format produces for the long ones
    ("""                piVar1 = &DAT_GameState::instance.playerDataArray[p]
                              .totalAttackTroops;
                *piVar1 = *piVar1 + 1;
""",
     "                DAT_GameState::instance.playerDataArray[p].totalAttackTroops = "
     "DAT_GameState::instance.playerDataArray[p].totalAttackTroops + 1;\n", 1),
    # declared on the spot: the type prefix goes with the pointer, or it is left stranded in
    # front of the lvalue and the file stops compiling
    ("""                            char* pcVar3 = &a.moats[t].someCountDown;
                            *pcVar3 = *pcVar3 + -0x14;
""",
     "                            a.moats[t].someCountDown = a.moats[t].someCountDown + -0x14;\n", 1),
    # something other than a plain increment on the right
    ("""            psVar4 = &a.b;
            *psVar4 = *psVar4 - c * 2;
""",
     "            a.b = a.b - c * 2;\n", 1),
    # set up here, dereferenced further down: the index could change in between, so leave it
    ("""            psVar4 = &this->units[k].field97;
            if (this->units[k].field97 > 0) {
                *psVar4 = *psVar4 + 1;
            }
""",
     """            psVar4 = &this->units[k].field97;
            if (this->units[k].field97 > 0) {
                *psVar4 = *psVar4 + 1;
            }
""", 0),
    # a store through a different pointer than the one just assigned
    ("""            piVar1 = &a.b;
            *piVar2 = *piVar2 + 1;
""",
     """            piVar1 = &a.b;
            *piVar2 = *piVar2 + 1;
""", 0),
    # a plain pointer that is not a decompiler name is none of our business
    ("""            rowPtr = &a.b;
            *rowPtr = *rowPtr + 1;
""",
     """            rowPtr = &a.b;
            *rowPtr = *rowPtr + 1;
""", 0),
]

if __name__ == "__main__":
    failures = 0
    for src, want, want_n in CASES:
        got, n = unptr.process(src)
        ok = got == want and n == want_n
        failures += not ok
        print("%-4s %s" % ("ok" if ok else "FAIL", src.strip().split("\n")[0]))
        if not ok:
            print("       got  %r (%d)\n       want %r (%d)" % (got, n, want, want_n))
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
