"""Run an original function under unicorn and read back what it wrote.

usage:
  orig_emulate.py 0xADDRESS --this-size N [--arg V]... [--dump OFF:COUNT[:i|h|b]]...

For a function whose job is to fill a table - `setTileSystemMemoryLookupArrays` writes ~1.9 MB of lookup
arrays into `this` - a match percentage says little about whether a rewrite computes the same thing, and
the game has to be run to find out. This maps the original image, gives the function a zeroed `this` of
N bytes in ecx and the given stack arguments, runs it to its return, and prints the requested ranges of
`this` as ints (i), shorts (h) or bytes (b). Compare that against a model of the rewrite in Python, or
against the same ranges written by our DLL.

Only self-contained code runs this way: the image's globals are as stored in the file, imports are not
resolved, and a call into the CRT or the OS faults. Use it as a library for anything more involved:

    import orig_emulate
    uc, this = orig_emulate.run(0x4e2050, 0x19f008)
    tiles = orig_emulate.read_ints(uc, this + 0x4e600, 321602)

Needs `pip install unicorn`.
"""

import struct
import sys

import common


def load():
    from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
    image = common.original_image()
    d = image.data
    pe = struct.unpack_from("<I", d, 0x3c)[0]
    size = struct.unpack_from("<I", d, pe + 24 + 56)[0]  # SizeOfImage
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(image.image_base, (size + 0xfff) & ~0xfff)
    for vsize, vaddr, rsize, raw in image.sections:
        uc.mem_write(image.image_base + vaddr, d[raw:raw + min(rsize, vsize or rsize)])
    return uc


def run(va, this_size, args=(), this_base=0x30000000, stack=0x20000000, stack_size=0x400000):
    """Call the function at va as __thiscall on a zeroed object; returns (uc, this address)."""
    from unicorn.x86_const import UC_X86_REG_ECX, UC_X86_REG_ESP
    uc = load()
    uc.mem_map(stack - stack_size, stack_size + 0x1000)
    uc.mem_map(this_base, (this_size + 0xfff) & ~0xfff)
    ret = 0x10000000
    uc.mem_map(ret, 0x1000)
    sp = stack - 0x100
    for a in reversed(args):
        sp -= 4
        uc.mem_write(sp, struct.pack("<i", a))
    sp -= 4
    uc.mem_write(sp, struct.pack("<I", ret))
    uc.reg_write(UC_X86_REG_ESP, sp)
    uc.reg_write(UC_X86_REG_ECX, this_base)
    uc.emu_start(va, ret)
    return uc, this_base


def read_ints(uc, address, count, fmt="i"):
    size = struct.calcsize("<" + fmt)
    return list(struct.unpack("<%d%s" % (count, fmt), bytes(uc.mem_read(address, size * count))))


def main():
    argv = sys.argv[1:]
    if not argv or "--this-size" not in argv:
        sys.exit(__doc__)
    va = int(argv[0], 16)
    this_size = int(argv[argv.index("--this-size") + 1], 0)
    args = [int(argv[k + 1], 0) for k, a in enumerate(argv) if a == "--arg"]
    dumps = [argv[k + 1] for k, a in enumerate(argv) if a == "--dump"]
    uc, this = run(va, this_size, args)
    for spec in dumps:
        parts = spec.split(":")
        off, count = int(parts[0], 0), int(parts[1], 0)
        fmt = parts[2] if len(parts) > 2 else "i"
        print("+%#x: %s" % (off, " ".join(str(v) for v in read_ints(uc, this + off, count, fmt))))


if __name__ == "__main__":
    main()
