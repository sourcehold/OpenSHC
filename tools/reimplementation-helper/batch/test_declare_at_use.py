"""Checks for declare_at_use.py's scope rule.

The tool had no tests, which is how two defects reached the tree: it wrote in place with
no dry run, and it moved a declaration into a do-block whose `while` condition could then
not see it, which does not compile. The cause was depths() recording the depth a line
opens at, so a use on a `} while (cond);` line looked like it sat inside the block.

usage:
  test_declare_at_use.py
"""

import os
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import declare_at_use

HEAD = """// FUNCTION: STRONGHOLDCRUSADER 0x00400000
void f()
{
"""

# (name, body, variable whose declaration must stay at the top or None,
#  variable whose declaration must have moved or None)
CASES = [
    ("do-while condition", """    bool bVar3;
    int iVar7;
    do {
        bVar3 = false;
        iVar7 = 0;
    } while (bVar3);
}
""", "bVar3", "iVar7"),
    ("top-level assignment", """    int iVar1;
    iVar1 = 3;
    use(iVar1);
}
""", None, "iVar1"),
    ("use after inner block", """    int iVar2;
    if (c) {
        iVar2 = 1;
    }
    use(iVar2);
}
""", "iVar2", None),
    # a later case label jumps over the initialisation (C2360), and the label can sit
    # after the last use, so the declaration has to stay put
    ("switch arm", """    int imageX;
    switch (k) {
    case 1:
        imageX = 0;
        use(imageX);
        break;
    case 2:
        use(0);
        break;
    }
}
""", "imageX", None),
    # an assignment inside a comma expression in a condition is not a statement, so no
    # declaration can replace it
    ("comma expression", """    int local_8;
    int iVar1;
    if ((-1 < k)
        && (iVar1 = p->idx,
            local_8 = n * 4,
            iVar1 < p->len)) {
        use(local_8);
    }
}
""", "local_8", None),
    ("unused is dropped", """    int iVar4;
    use(0);
}
""", None, "iVar4"),
]


def run(body):
    path = os.path.join(tempfile.mkdtemp(), "f.cpp")
    with open(path, "w", encoding="utf-8", newline="") as fh:
        fh.write(HEAD + body)
    declare_at_use.move(path, write=True)
    with open(path, encoding="utf-8") as fh:
        return fh.read()


if __name__ == "__main__":
    failures = 0
    for name, body, keep, gone in CASES:
        out = run(body)
        notes = []
        if keep and ("    %s " % keep) not in out and (" %s;" % keep) not in out:
            notes.append("%s lost its declaration" % keep)
        if gone and (" %s;" % gone) in out.split("\n")[3:5][0]:
            notes.append("%s was not moved" % gone)
        failures += bool(notes)
        print("%-4s %-22s %s" % ("ok" if not notes else "FAIL", name,
                                 "; ".join(notes) or "as expected"))
        if notes:
            print("---- got:\n%s----" % out)
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
