"""Disassemble an original function from `_original/` in full, with correct bounds.

usage: orig_body.py (FILE.cpp | 0xADDRESS) [--count] [--end 0xADDR] [--raw]

`orig_asm.py` prints the original stream as recorded in `reccmp/dll/diff.json`, and that
stream is **not the whole function**: reccmp reads our function's byte length from our PDB and
dumps that many bytes from the original's address, so whenever our code is shorter in bytes the
original is clipped. `aiGiveRaidInstructions` is clipped 42 bytes early and ends mid-call-setup
on `push edx; push eax`, with no `ret` anywhere - which makes a function that plainly has one
look like it ends on two pushes, and makes any comparison of instruction counts or of
tail-end code meaningless.

This reads the bytes out of `_original/Stronghold Crusader.exe` instead and finds the end
itself: walk forward tracking the furthest forward branch target, and stop at the first `ret`
or `jmp` that sits at or past that target. Nothing can jump over the end of a function, so a
`ret` with no pending forward target beyond it is the end. On `aiGiveRaidInstructions` that
gives `0x4d2dff`, matching Ghidra's body range `004d2a70 - 004d2dfe` exactly.

The heuristic can still be fooled - by a function whose last instruction is a conditional
branch, or by one the linker split - so `--end` overrides it, and Ghidra's
`get_function_by_address` is the second opinion worth taking. Ghidra is not always right
either; where the two disagree, read the bytes.

`--count` prints a mnemonic histogram instead of the listing, which is what structural work
needs. Mnemonics are canonicalised first (`jz` to `je`, `jnz` to `jne`, and so on) because
capstone and reccmp spell the same instruction differently, and an uncanonicalised comparison
invents differences that are not there.

Other modules import `disassemble`, `histogram` and `find_end` from here.
"""

import re
import struct
import sys

import capstone

import common

# capstone and reccmp disagree on the spelling of several instructions; comparing without
# folding these invents differences that do not exist
SYNONYMS = {
    'jz': 'je', 'jnz': 'jne', 'jc': 'jb', 'jnc': 'jae', 'jnb': 'jae', 'jnbe': 'ja',
    'jnae': 'jb', 'jna': 'jbe', 'jnge': 'jl', 'jnl': 'jge', 'jng': 'jle', 'jnle': 'jg',
    'jpe': 'jp', 'jpo': 'jnp', 'setz': 'sete', 'setnz': 'setne', 'setc': 'setb',
    'setnc': 'setae', 'setnbe': 'seta', 'setnge': 'setl', 'setnl': 'setge',
    'setng': 'setle', 'setnle': 'setg', 'sal': 'shl', 'cmovz': 'cmove',
    'cmovnz': 'cmovne', 'repe': 'rep', 'repz': 'rep', 'retn': 'ret',
}
PADDING = ('int3', 'nop')
# MSVC pads with nop-equivalents rather than `nop`: `lea esp, [esp]`, `lea ecx, [ecx]` and
# `mov edi, edi`. They are not real memory references, and anything reading stack operands has
# to skip them or `lea esp, [esp]` reads as a reference to the slot at the current esp.
_NOP_LEA = re.compile(r'^(\w+), \[\1(?: \+ 0x0)?\]$')


def is_padding(mnemonic, ops):
    """True for an instruction that only exists to fill space."""
    if mnemonic in PADDING:
        return True
    if mnemonic == 'lea' and _NOP_LEA.match(ops):
        return True
    return mnemonic == 'mov' and ops.replace(' ', '') == 'edi,edi'


def canon(mnemonic):
    return SYNONYMS.get(mnemonic, mnemonic)


class Image(object):
    """The original executable, with address-to-file-offset mapping."""

    def __init__(self, path=None):
        path = path or (common.ROOT / '_original' / 'Stronghold Crusader.exe')
        self.data = open(str(path), 'rb').read()
        d = self.data
        pe = struct.unpack_from('<I', d, 0x3c)[0]
        nsec = struct.unpack_from('<H', d, pe + 6)[0]
        optsz = struct.unpack_from('<H', d, pe + 20)[0]
        self.base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
        self.secs = []
        for i in range(nsec):
            o = pe + 24 + optsz + 40 * i
            vs, va, rs, rp = struct.unpack_from('<IIII', d, o + 8)
            self.secs.append((va, vs, rp, rs))

    def offset(self, va):
        r = va - self.base
        for va_s, vs, rp, rs in self.secs:
            if va_s <= r < va_s + max(vs, rs):
                return r - va_s + rp
        return None


def find_end(image, start, limit=0x4000):
    """First address past the function.

    Walks forward tracking the furthest forward branch target and stops at the first `ret` or
    `jmp` at or beyond it, because nothing branches over the end of a function.
    """
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    off = image.offset(start)
    if off is None:
        raise ValueError('address %#x is not in a mapped section' % start)
    furthest = start
    for ins in md.disasm(image.data[off:off + limit], start):
        if ins.mnemonic.startswith('j') and ins.op_str.startswith('0x'):
            target = int(ins.op_str, 16)
            if target > furthest:
                furthest = target
        if canon(ins.mnemonic) in ('ret', 'jmp') and ins.address >= furthest:
            return ins.address + ins.size
    return None


def disassemble(start, end=None, image=None):
    """[(address, mnemonic, operands)] for one original function, padding dropped."""
    image = image or Image()
    end = end or find_end(image, start)
    if end is None:
        raise ValueError('could not find the end of the function at %#x' % start)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    off = image.offset(start)
    out = []
    for ins in md.disasm(image.data[off:off + (end - start)], start):
        if ins.mnemonic in PADDING:
            continue
        out.append((ins.address, canon(ins.mnemonic), ins.op_str))
    return out


def histogram(stream):
    counts = {}
    for _a, m, _o in stream:
        counts[m] = counts.get(m, 0) + 1
    return counts


def address_of(arg):
    """An explicit 0x address, or the `// FUNCTION:` marker of a source file."""
    if arg.lower().startswith('0x'):
        return int(arg, 16)
    text = common.read_text(arg)
    m = re.search(r'FUNCTION: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)', text)
    if not m:
        sys.exit('%s has no `// FUNCTION:` marker' % arg)
    return int(m.group(1), 16)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    if not args:
        sys.exit(__doc__)
    end = None
    for a in sys.argv[1:]:
        if a.startswith('--end'):
            end = int(a.split('=', 1)[1], 16) if '=' in a else None
    if end is None and '--end' in sys.argv:
        i = sys.argv.index('--end')
        if i + 1 < len(sys.argv):
            end = int(sys.argv[i + 1], 16)
    start = address_of(args[0])
    image = Image()
    detected = find_end(image, start)
    use = end or detected
    stream = disassemble(start, use, image)
    print('# %#x .. %#x   %d instructions   %d bytes%s'
          % (start, use, len(stream), use - start,
             '   (--end override; detected %#x)' % detected if end and end != detected else ''))
    if '--count' in sys.argv:
        counts = histogram(stream)
        for m in sorted(counts, key=lambda k: -counts[k]):
            print('%6d  %s' % (counts[m], m))
        return
    for addr, mnemonic, ops in stream:
        print('%08x  %-7s %s' % (addr, mnemonic, ops))


if __name__ == '__main__':
    main()
