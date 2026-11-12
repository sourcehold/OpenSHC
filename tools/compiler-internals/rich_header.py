#!/usr/bin/env python
"""Decode the Rich header of a PE file: which tools built its objects, and how many each.

    python tools/compiler-internals/rich_header.py "_original/Stronghold Crusader.exe"
    python tools/compiler-internals/rich_header.py build-RelWithDebInfo/DLL/OpenSHC.dll

Every object the linker consumed carries a product id and a build number; the linker counts them
into the Rich header. The ids below were measured with the bundled MSVC1400-SP1 toolchain (a one
line .c/.cpp/.asm each compiled, linked alone into a DLL, header read back), not copied from a
published table - the published table had 0x7d as "LTCG C++", and it is the assembler.
"""
import struct
import sys

KNOWN = {
    0x6d: 'cl 14.00, C, no /GL',
    0x6e: 'cl 14.00, C++, no /GL',
    0x71: 'cl 14.00 /GL, C   (LTCG)',
    0x72: 'cl 14.00 /GL, C++ (LTCG)',
    0x78: 'link 8.00',
    0x7a: '.exp object (/export)',
    0x7c: 'cvtres 8.00 (resources) - inferred, not measured',
    0x7d: 'ml 8.00 (MASM)',
    0x01: 'import thunks (one per imported function)',
    0x00: 'objects without a comp.id',
}


def decode(path):
    data = open(path, 'rb').read(0x1000)
    end = data.find(b'Rich')
    if end < 0:
        return None
    key = struct.unpack_from('<I', data, end + 4)[0]
    dans = struct.pack('<I', struct.unpack('<I', b'DanS')[0] ^ key)
    start = data.rfind(dans, 0, end)
    if start < 0:
        return None
    out = []
    pos = start + 16
    while pos + 8 <= end:
        value, count = struct.unpack_from('<II', data, pos)
        value ^= key
        count ^= key
        out.append((value >> 16, value & 0xffff, count))
        pos += 8
    return out


def main(argv):
    if not argv:
        print(__doc__)
        return 2
    for path in argv:
        print('== %s' % path)
        try:
            entries = decode(path)
        except IOError as e:
            print('   %s' % e)
            continue
        if entries is None:
            print('   no Rich header')
            continue
        for prod, build, count in sorted(entries, key=lambda e: (-e[1], e[0])):
            print('   id 0x%02x  build %5d  x%-5d %s' % (prod, build, count, KNOWN.get(prod, '')))
        gl = sum(c for p, b, c in entries if p in (0x71, 0x72))
        cxx = sum(c for p, b, c in entries if p in (0x6d, 0x6e, 0x71, 0x72))
        print('   /GL objects: %d of %d C/C++ objects' % (gl, cxx))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
