"""Compare the compiled computeHash object with a user's original SHC executable.

Requires Python 3.10+, pefile and unicorn. Does not launch or modify the game.
"""

import argparse
import hashlib
from pathlib import Path
import random
import struct

import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDI,
    UC_X86_REG_ESI, UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_EIP,
)


SYMBOL = b'?computeHash@DirectionAlgorithmState@Navigation@Map@OpenSHC@@QAEIHPAH@Z'


def object_code(path):
    """Read this function's relocation-free MSVC x86 COFF section."""
    data = path.read_bytes()
    machine, sections, _, symbols, count, optional, _ = struct.unpack_from('<HHIIIHH', data)
    assert machine == 0x14c and optional == 0, 'Expected an x86 COFF object'
    strings = symbols + count * 18
    index = 0
    while index < count:
        name, value, section, kind, _, auxiliary = struct.unpack_from(
            '<8sIhHBB', data, symbols + index * 18)
        if name[:4] == b'\0' * 4:
            offset = strings + struct.unpack_from('<I', name, 4)[0]
            name = data[offset:data.index(b'\0', offset)]
        else:
            name = name.rstrip(b'\0')
        if name == SYMBOL:
            assert kind == 0x20 and 1 <= section <= sections
            header = 20 + (section - 1) * 40
            size, offset = struct.unpack_from('<II', data, header + 16)
            relocations = struct.unpack_from('<H', data, header + 32)[0]
            assert relocations == 0, 'Function section must be self-contained'
            return data[offset + value:offset + size]
        index += 1 + auxiliary
    raise ValueError('computeHash function symbol missing from object')


def execute(code, payload, byte_count, alignment):
    cpu = Uc(UC_ARCH_X86, UC_MODE_32)
    code_base, stack, memory, stop = 0x100000, 0x200000, 0x400000, 0x300000
    cpu.mem_map(code_base, 0x1000)
    cpu.mem_write(code_base, code)
    cpu.mem_map(stack, 0x10000)
    cpu.mem_map(memory, 0x20000)
    address = memory + 0x100 + alignment
    cpu.mem_write(address, payload or b'\0')
    sp = stack + 0x8000
    cpu.mem_write(sp, struct.pack('<III', stop, byte_count & 0xffffffff, address))
    cpu.reg_write(UC_X86_REG_ESP, sp)
    # The original does not dereference its nominal this pointer.
    cpu.reg_write(UC_X86_REG_ECX, 0xdead0000)
    saved = {reg: 0x12340000 + reg for reg in
             (UC_X86_REG_EBX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)}
    for reg, value in saved.items():
        cpu.reg_write(reg, value)
    read_bytes = max(0, byte_count // 4 * 4)

    def check_read(uc, access, location, size, value, context):
        if stack <= location and location + size <= stack + 0x10000:
            return
        assert address <= location and location + size <= address + read_bytes, (
            'Read outside complete input words', hex(location), size, byte_count)

    def check_write(uc, access, location, size, value, context):
        assert stack <= location and location + size <= stack + 0x10000, (
            'Unexpected non-stack write', hex(location))

    cpu.hook_add(UC_HOOK_MEM_READ, check_read)
    cpu.hook_add(UC_HOOK_MEM_WRITE, check_write)
    cpu.emu_start(code_base, stop, count=500000)
    assert cpu.reg_read(UC_X86_REG_EIP) == stop, 'Function did not return'
    assert cpu.reg_read(UC_X86_REG_ESP) == sp + 12, 'Incorrect thiscall cleanup'
    for reg, value in saved.items():
        assert cpu.reg_read(reg) == value, 'Callee-saved register changed'
    return cpu.reg_read(UC_X86_REG_EAX)


def reference(payload, byte_count):
    result = 0
    for offset in range(0, max(0, byte_count - 3), 4):
        result = (result + struct.unpack_from('<I', payload, offset)[0]) & 0xffffffff
        result = ((result << 1) | (result >> 31)) & 0xffffffff
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('object', type=Path)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--address', type=lambda value: int(value, 0), default=0x46cd30)
    args = parser.parse_args()
    compiled = object_code(args.object)
    original_file = args.executable.read_bytes()
    pe = pefile.PE(data=original_file, fast_load=True)
    assert pe.FILE_HEADER.Machine == 0x14c
    original = pe.get_data(args.address - pe.OPTIONAL_HEADER.ImageBase, 0xb5)
    assert original[:6] == bytes.fromhex('55 8b ec 51 53 56')
    assert original[-3:] == bytes.fromhex('c2 08 00'), 'Unexpected native function'
    assert compiled == original, 'Compiled function differs from the original 181 bytes'
    print('PASS: all 181 function bytes match the original, including prologue and epilogue')
    rng = random.Random(0x46cd30)
    lengths = [-2147483648, -65, -4, -1] + list(range(132))
    lengths += [255, 256, 257, 1023, 1024, 4095, 4096, 65535, 65536]
    lengths += [rng.randrange(0, 8193) for _ in range(100)]
    cases = 0
    for byte_count in lengths:
        size = max(0, byte_count)
        for pattern in (b'\x00', b'\xff', b'\x00\x00\x00\x80', None):
            payload = (pattern * (size // len(pattern) + 1))[:size] if pattern else rng.randbytes(size)
            alignment = cases % 4
            expected = reference(payload, byte_count)
            assert execute(original, payload, byte_count, alignment) == expected, ('original', byte_count)
            assert execute(compiled, payload, byte_count, alignment) == expected, ('C++', byte_count)
            cases += 1
    print(f'PASS: {cases} native/C++ comparisons, including memory bounds and x86 thiscall ABI')
    print(f'Executable SHA256: {hashlib.sha256(original_file).hexdigest()}')
    print(f'Object SHA256: {hashlib.sha256(args.object.read_bytes()).hexdigest()}')


if __name__ == '__main__':
    main()
