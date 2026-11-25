"""Name -> virtual address for every public symbol in c2.pdb, by scanning S_PUB32 records.

Ghidra has the PDB loaded, but only `get_function_by_address` honours ghidra-mcp's `program`
argument - the name searches ignore it and query whatever program is current - so a local map is
the practical way to go from a name to an address.

An S_PUB32 record is

    u16 reclen | u16 rectyp = 0x110e | u32 flags | u32 offset | u16 segment | zero-terminated name

so the records can be found by scanning for the type word and validating the length against the
name that follows. Segment is a 1-based index into the PE section table, which turns
(segment, offset) into a virtual address.

usage: pdbnames.py [SUBSTRING ...]      case-insensitive; no argument dumps the count only
"""

import re
import struct
import sys

PDB = r'C:\Users\Gynt\Projects\sourcehold\ghidra\symbol-servers\c2.pdb\8E3C6AD714BE4E55B528B0DBEB3BABD81\c2.pdb'
DLL = r'C:\Users\Gynt\Projects\sourcehold\rea\OpenSHC-2\MSVC1400-SP1\VC\bin\c2.dll'
S_PUB32 = 0x110e


def sections(path):
    d = open(path, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    nsec = struct.unpack_from('<H', d, pe + 6)[0]
    optsz = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
    out = []
    for i in range(nsec):
        o = pe + 24 + optsz + 40 * i
        name = d[o:o + 8].rstrip(b'\0').decode('latin1')
        va = struct.unpack_from('<I', d, o + 12)[0]
        out.append((name, va))
    return base, out


def publics():
    data = open(PDB, 'rb').read()
    base, secs = sections(DLL)
    found = {}
    pos = 0
    while True:
        pos = data.find(struct.pack('<H', S_PUB32), pos)
        if pos < 0:
            break
        # the type word is preceded by the record length
        if pos < 2:
            pos += 2
            continue
        reclen = struct.unpack_from('<H', data, pos - 2)[0]
        if not (14 <= reclen <= 4096):
            pos += 2
            continue
        try:
            _flags, offset, seg = struct.unpack_from('<IIH', data, pos + 2)
        except struct.error:
            break
        nstart = pos + 12
        nend = data.find(b'\0', nstart, nstart + reclen)
        if nend < 0 or not (1 <= seg <= len(secs)):
            pos += 2
            continue
        name = data[nstart:nend]
        # the record must be exactly as long as it claims, allowing the 4-byte alignment pad
        actual = (nend - (pos - 2)) + 1
        if not (reclen + 2 - 4 <= actual <= reclen + 2):
            pos += 2
            continue
        if name and re.match(rb'^[\x20-\x7e]+$', name):
            va = base + secs[seg - 1][1] + offset
            found.setdefault(name.decode('latin1'), va)
        pos += 2
    return found


if __name__ == '__main__':
    syms = publics()
    print('%d public symbol(s) recovered' % len(syms))
    pats = [a.lower() for a in sys.argv[1:]]
    if not pats:
        sys.exit(0)
    for name in sorted(syms):
        low = name.lower()
        if any(p in low for p in pats):
            print('  %#010x  %s' % (syms[name], name))
