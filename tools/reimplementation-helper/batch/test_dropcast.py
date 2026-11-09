"""Cases for dropcast.py.

usage:
  test_dropcast.py
"""

import dropcast

HEADERS = ["""
struct Unit {
    short drawX; // 0x0
    byte* bytes; // 0x4
    byte b; // 0x8
    short arr[4]; // 0xa
    uint count; // 0x14
};
struct A {
    short value; // 0x0
};
struct B {
    int value; // 0x0
};
"""]
GLOBALS = ["MACRO_STRUCT_RESOLVER(Unit, false, Address::SHC_3BB0A8C1_0x00400000) DAT_Unit;"]

HEAD = """// FUNCTION: STRONGHOLDCRUSADER 0x00400000
void Unit::f(short a, uint u)
{
    short s = 0;
    int k = 0;
"""
TAIL = "}\n"

CASES = [
    # a short field of a global
    ("x = (int)DAT_Unit::instance.drawX;", "x = DAT_Unit::instance.drawX;", 1),
    # a field reached through `this`, typed by the function's own class
    ("x = (int)this->drawX + 1;", "x = this->drawX + 1;", 1),
    # an indexed pointer field is its element...
    ("x = (int)DAT_Unit::instance.bytes[3];", "x = DAT_Unit::instance.bytes[3];", 1),
    # ...but the pointer itself is not a narrow integer (an earlier version stripped the `*`)
    ("x = (int)DAT_Unit::instance.bytes;", "x = (int)DAT_Unit::instance.bytes;", 0),
    # an array field indexed
    ("x = (int)DAT_Unit::instance.arr[i];", "x = DAT_Unit::instance.arr[i];", 1),
    # an unsigned int field is no narrower than the cast
    ("x = (int)DAT_Unit::instance.count;", "x = (int)DAT_Unit::instance.count;", 0),
    # short locals and parameters, and an int local
    ("x = (int)s + (int)a + (int)k;", "x = s + a + k;", 3),
    # a uint parameter keeps its cast: this one converts
    ("x = (int)u;", "x = (int)u;", 0),
    # a whole int expression in brackets
    ("x = (int)(DAT_Unit::instance.drawX + 4) * 2;", "x = (DAT_Unit::instance.drawX + 4) * 2;", 1),
    # ...as an argument, where it needs no brackets of its own
    ("g((int)(s + 1), k);", "g(s + 1, k);", 1),
    # an expression with an unsigned operand converts, so it stays
    ("x = (int)(u + 1);", "x = (int)(u + 1);", 0),
    # a literal that is not an int keeps the cast
    ("x = (int)(s + 0x80000000);", "x = (int)(s + 0x80000000);", 0),
    # a call is not an lvalue whose type is known
    ("x = (int)h(s);", "x = (int)h(s);", 0),
    # a field name that is short in one struct and int in another: unknown, keep it
    ("x = (int)p->value;", "x = (int)p->value;", 0),
    # a narrow unsigned subscript drops its (uint)...
    ("x = t[(uint)DAT_Unit::instance.b];", "x = t[DAT_Unit::instance.b];", 1),
    # ...a signed one does not: there the cast changes the index
    ("x = t[(uint)DAT_Unit::instance.drawX];", "x = t[(uint)DAT_Unit::instance.drawX];", 0),
]

if __name__ == "__main__":
    types = dropcast.Types(HEADERS, GLOBALS)
    failures = 0
    for stmt, want, want_n in CASES:
        got, n = dropcast.process(HEAD + "    " + stmt + "\n" + TAIL, types)
        want_text = HEAD + "    " + want + "\n" + TAIL
        ok = got == want_text and n == want_n
        failures += not ok
        print("%-4s %s" % ("ok" if ok else "FAIL", stmt))
        if not ok:
            print("       got  %r (%d)\n       want %r (%d)" % (got[len(HEAD):], n, want, want_n))
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
