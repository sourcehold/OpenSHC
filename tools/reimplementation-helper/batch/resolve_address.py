"""Resolve hard-coded game addresses in the sources to `DAT_X::instance.field` paths.

Ghidra leaves absolute addresses of the original's globals in the decompiled output, as loop
bounds (`while ((int)p < 0x17802b4)`) and as bases (`*(byte*)(tile + 0x1ee2998)`). They are not
just unreadable: our DLL's resolver instances live elsewhere, so a literal address reads the wrong
memory at runtime and never matches the original's asm.

usage: resolve_address.py [filter]        report every literal in the matching sources
       resolve_address.py 0x1ee2998 ...   resolve single addresses
"""

import re
import sys

import common

GLOBAL_RE = re.compile(r"//\s*GLOBAL:\s*STRONGHOLDCRUSADER\s+(0x[0-9A-Fa-f]+)")
RESOLVER_RE = re.compile(r"MACRO_STRUCT_RESOLVER\((\w+),\s*\w+,\s*[\w:]+\)\s*(\w+);")
DECL_RE = re.compile(r"^\s*(?:(?:const|static)\s+)?([A-Za-z_][\w:]*)\s+(\w+)((?:\[\d+\])*)\s*;"
                     r"\s*//\s*(0x[0-9A-Fa-f]+)\s+length:\s*(\d+)")
SIZE_RE = re.compile(r"static_assert_cpp98_obj\(sizeof\((\w+)\) == (\d+)")
SCALARS = {"byte": 1, "char": 1, "undefined1": 1, "bool": 1, "uchar": 1,
           "short": 2, "ushort": 2, "undefined2": 2, "word": 2,
           "int": 4, "uint": 4, "undefined4": 4, "dword": 4, "float": 4, "long": 4, "ulong": 4}

_structs = {}


def struct_of(name):
    """{name: (type, offset, dims)} plus its size, parsed from the header that defines it."""
    if name in _structs:
        return _structs[name]
    _structs[name] = None
    for path in common.ROOT.joinpath("src/OpenSHC").rglob("%s.hpp" % name.split("::")[-1]):
        text = path.read_text(encoding="utf-8", errors="replace")
        if not re.search(r"\b(?:struct|class)\s+%s\b" % name.split("::")[-1], text):
            continue
        fields = []
        for line in text.splitlines():
            m = DECL_RE.match(line)
            if m:
                fields.append((m.group(2), m.group(1), int(m.group(4), 16),
                               [int(d) for d in re.findall(r"\[(\d+)\]", m.group(3))], int(m.group(5))))
        m = SIZE_RE.search(text)
        if fields:
            _structs[name] = (fields, int(m.group(2)) if m else None)
        break
    return _structs[name]


def path_of(type_name, offset, depth=0):
    """Field path inside `type_name` for a byte offset, e.g. `.playerInfo[2].wide3`."""
    if depth > 6:
        return None
    info = struct_of(type_name)
    if info is None:
        return None
    for name, ftype, foff, dims, length in info[0]:
        if not foff <= offset < foff + length:
            continue
        rel = offset - foff
        count = 1
        for d in dims:
            count *= d
        elem = length // count if count else length
        index = ""
        if dims:
            flat = rel // elem
            rel -= flat * elem
            for d in reversed(dims):
                index = "[%d]" % (flat % d) + index
                flat //= d
        if ftype in SCALARS or ftype.startswith("undefined"):
            return ".%s%s" % (name, index) + ("+%d" % rel if rel else "")
        inner = path_of(ftype, rel, depth + 1)
        if inner is None:
            return ".%s%s" % (name, index) + ("+%d" % rel if rel else "")
        return ".%s%s%s" % (name, index, inner)
    return "+%d" % offset


def globals_index():
    out = []
    for path in sorted(common.ROOT.glob("src/OpenSHC/Globals/*.hpp")):
        text = path.read_text(encoding="utf-8", errors="replace")
        g, r = GLOBAL_RE.search(text), RESOLVER_RE.search(text)
        if not g or not r:
            continue
        base, type_name, var = int(g.group(1), 16), r.group(1), r.group(2)
        info = struct_of(type_name)
        size = info[1] if info and info[1] else SCALARS.get(type_name, 4)
        out.append((base, base + size, var, type_name))
    return sorted(out)


INDEX = globals_index()


def resolve(address):
    for base, end, var, type_name in INDEX:
        if base <= address < end:
            return "%s::instance%s" % (var, path_of(type_name, address - base) or "+%d" % (address - base))
    return None


args = [a for a in sys.argv[1:]]
if args and args[0].startswith("0x"):
    for a in args:
        print("%-12s %s" % (a, resolve(int(a, 16)) or "no global covers this address"))
    sys.exit()

filter_ = args[0] if args else ""
LITERAL = re.compile(r"0x1[0-9a-f]{6}\b")
total = 0
for f in common.list_files():
    if filter_ not in f:
        continue
    text = common.read_text(f)
    hits = {}
    for n, line in enumerate(text.splitlines(), 1):
        for lit in LITERAL.findall(line):
            hits.setdefault(lit, []).append(n)
    if not hits:
        continue
    print("### %s" % f.split("/")[-1])
    for lit, lines in sorted(hits.items()):
        print("  %-12s %-4s %s" % (lit, len(lines), resolve(int(lit, 16)) or "UNRESOLVED"))
        total += len(lines)
print("%d literal address(es)" % total)
