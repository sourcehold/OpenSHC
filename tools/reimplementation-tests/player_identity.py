"""Compare the compiled player-handle translator to both original game variants.

Requires pefile and unicorn. Reads files only; never launches the game.
"""
import argparse
import hashlib
from pathlib import Path
import random
import struct

import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX,
    UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_EIP)

SYMBOL = b'?translateMultiplayerIDsIntoPlayerIDs@GameSynchronyState@Synchrony@OpenSHC@@QAEIH@Z'
VARIANTS = {
    '3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a': (0x47eaf0, 0x109e74),
    '55648e6b05d67d37a5773fe699bbb17a2d6ad4de1bb9dbded9a21caef82bd7fb': (0x47ecc0, 0x166304),
}


def object_code(path):
    data = path.read_bytes()
    machine, sections, _, symbols, count, optional, _ = struct.unpack_from('<HHIIIHH', data)
    assert machine == 0x14c and optional == 0
    strings = symbols + count * 18
    index = 0
    while index < count:
        name, value, section, kind, _, auxiliary = struct.unpack_from('<8sIhHBB', data, symbols + index * 18)
        if name[:4] == b'\0' * 4:
            offset = strings + struct.unpack_from('<I', name, 4)[0]
            name = data[offset:data.index(b'\0', offset)]
        else:
            name = name.rstrip(b'\0')
        if name == SYMBOL:
            assert kind == 0x20 and 1 <= section <= sections
            header = 20 + (section - 1) * 40
            size, offset = struct.unpack_from('<II', data, header + 16)
            assert struct.unpack_from('<H', data, header + 32)[0] == 0, 'Unexpected relocations'
            return data[offset + value:offset + size]
        index += 1 + auxiliary
    raise ValueError('Player identity function is missing')


def execute(code, mode, local_player, handles, sender, local_offset, relocated):
    cpu = Uc(UC_ARCH_X86, UC_MODE_32)
    start, stack, stop = 0x100000, 0x200000, 0x300000
    state = 0x800000 if relocated else 0x400000
    cpu.mem_map(start, 0x1000); cpu.mem_write(start, code)
    cpu.mem_map(stack, 0x10000); cpu.mem_map(state, 0x200000)
    def put(address, value): cpu.mem_write(address, struct.pack('<I', value & 0xffffffff))
    put(state + 0x618, mode); put(state + local_offset, local_player)
    for index, handle in enumerate(handles): put(state + 0x6a8 + index * 4, handle)
    sp = stack + 0x8000
    put(sp, stop); put(sp + 4, sender)
    saved = {register: 0x12340000 + register for register in
             (UC_X86_REG_EBX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)}
    for register, value in saved.items(): cpu.reg_write(register, value)
    cpu.reg_write(UC_X86_REG_ESP, sp); cpu.reg_write(UC_X86_REG_ECX, state)
    reads = []
    def read(uc, access, location, size, value, context):
        if stack <= location and location + size <= stack + 0x10000: return
        assert (location == state + 0x618 or location == state + local_offset or
                state + 0x6ac <= location <= state + 0x6c8) and size == 4, 'Unexpected state read'
        reads.append(location - state)
    def write(uc, access, location, size, value, context):
        assert stack <= location and location + size <= stack + 0x10000, 'Unexpected state write'
    cpu.hook_add(UC_HOOK_MEM_READ, read); cpu.hook_add(UC_HOOK_MEM_WRITE, write)
    cpu.emu_start(start, stop, count=1000)
    assert cpu.reg_read(UC_X86_REG_EIP) == stop and cpu.reg_read(UC_X86_REG_ESP) == sp + 8
    assert cpu.reg_read(UC_X86_REG_ECX) == state, 'Native callers retain this in ECX'
    for register, value in saved.items(): assert cpu.reg_read(register) == value
    if mode in (0, 99): assert reads == [0x618, local_offset], 'Single-player must not inspect handles'
    return cpu.reg_read(UC_X86_REG_EAX)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path); parser.add_argument('executable', type=Path)
    args = parser.parse_args()
    data = args.executable.read_bytes(); digest = hashlib.sha256(data).hexdigest()
    assert digest in VARIANTS, 'Unsupported original executable'
    address, local_offset = VARIANTS[digest]
    pe = pefile.PE(data=data, fast_load=True)
    native = pe.get_data(address - pe.OPTIONAL_HEADER.ImageBase, 0x89)
    compiled = object_code(args.object)
    assert native[:8] == bytes.fromhex('8b 91 18 06 00 00 33 c0') and native[-3:] == b'\xc2\x04\0'
    rng = random.Random(0x47eaf0)
    rosters = [list(range(9)), [-1] * 9, [0] * 9, [123, 7, 8, 7, 9, 10, 7, 11, 7]]
    rosters += [[rng.randrange(-3, 10) for _ in range(9)] for _ in range(50)]
    cases = 0
    for mode in (0, 99, 1, 2, 666, -1):
        for handles in rosters:
            for sender in sorted(set(handles + [0x7fffffff, -2147483648, 0, -1])):
                local_player = rng.randrange(1, 9)
                matches = [i for i in range(1, 9) if handles[i] == sender]
                expected = local_player if mode in (0, 99) else max(matches, default=0)
                for code, offset in ((native, local_offset), (compiled, 0x109e74)):
                    assert execute(code, mode, local_player, handles, sender, offset, cases % 2) == expected
                cases += 1
    print(f'PASS: {cases} native/C++ identity comparisons; input bounds, read-only state, ECX and thiscall ABI')
    print(f'Native/compiled lengths: {len(native)}/{len(compiled)} bytes; exact bytes: {native == compiled}')
    print(f'Executable SHA256: {digest}')


if __name__ == '__main__': main()
