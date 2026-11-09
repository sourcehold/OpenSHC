"""Read code out of the original executable: disassembly and switch jump tables.

Used by jump_table_order.py; also runnable to look at a function:

    python original_asm.py UpdateDeer              # disassembly until the final ret
    python original_asm.py UpdateDeer --jumptable  # case values per switch body, in body order
    python original_asm.py 0x00541DE0              # an address works too

Needs capstone (pip install capstone) and _original/Stronghold Crusader.exe.
"""

import re
import struct
import sys
from pathlib import Path

import common

EXE = Path("_original/Stronghold Crusader.exe")

# units[0].state inside the resolved global UnitsState; the state switches dispatch on it
STATE_FIELD = 0x138880C


class Image(object):
    """The original exe, mapping virtual addresses to file offsets."""

    def __init__(self, path=EXE):
        if not path.exists():
            sys.exit("%s not found (link the original installation through _original/)" % path)
        self.data = path.read_bytes()
        pe = struct.unpack_from("<I", self.data, 0x3C)[0]
        sections = struct.unpack_from("<H", self.data, pe + 6)[0]
        optional_size = struct.unpack_from("<H", self.data, pe + 20)[0]
        self.imagebase = struct.unpack_from("<I", self.data, pe + 24 + 28)[0]
        self.sections = []
        offset = pe + 24 + optional_size
        for _ in range(sections):
            vsize, vaddr, rawsize, rawptr = struct.unpack_from("<IIII", self.data, offset + 8)
            self.sections.append((vaddr, max(vsize, rawsize), rawptr))
            offset += 40

    def offset(self, address):
        rva = address - self.imagebase
        for vaddr, size, rawptr in self.sections:
            if vaddr <= rva < vaddr + size:
                return rawptr + rva - vaddr
        raise ValueError("address %#x is outside the image" % address)

    def byte(self, address):
        return self.data[self.offset(address)]

    def dword(self, address):
        return struct.unpack_from("<I", self.data, self.offset(address))[0]


_image = None


def image():
    global _image
    if _image is None:
        _image = Image()
    return _image


def disassemble(address, max_instructions=4000):
    """Disassemble from address up to the last ret (following forward jumps) or the instruction limit.

    Returns a list of "%08x  mnemonic operands" strings.
    """
    import capstone

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    img = image()
    out = []
    furthest_jump = address
    for instruction in md.disasm(img.data[img.offset(address):img.offset(address) + 0x8000], address):
        out.append("%08x  %s %s" % (instruction.address, instruction.mnemonic, instruction.op_str))
        if instruction.mnemonic.startswith("j") and instruction.op_str.startswith("0x"):
            furthest_jump = max(furthest_jump, int(instruction.op_str, 16))
        if instruction.mnemonic == "ret" and instruction.address >= furthest_jump:
            break
        if len(out) >= max_instructions:
            break
    return out


_JUMP_RE = re.compile(r"jmp dword ptr \[(\w+)\*4 \+ (0x[0-9a-f]+)\]")
_INDEX_RE = re.compile(r"movzx \w+, byte ptr \[\w+ \+ (0x[0-9a-f]+)\]")
_MAX_RE = re.compile(r"cmp \w+, (0x[0-9a-f]+|\d+)$")
_MAX_REG_RE = re.compile(r"mov \w+, (0x[0-9a-f]+|\d+)$")
_DEFAULT_RE = re.compile(r"ja (0x[0-9a-f]+)")


def jump_tables(asm):
    """Find every `jmp dword ptr [reg*4 + table]` dispatch in a disassembly.

    Each result: table, index (byte index table, None if the jump table is indexed directly),
    maximum case value, default target and the offset of the field being switched on.
    """
    found = []
    for i, line in enumerate(asm):
        m = _JUMP_RE.search(line)
        if not m:
            continue
        table, index, maximum, default, field = int(m.group(2), 16), None, None, None, None
        for previous in asm[max(0, i - 8):i]:
            mm = _INDEX_RE.search(previous)
            if mm:
                index = int(mm.group(1), 16)
            mm = _MAX_RE.search(previous)
            if mm:
                maximum = int(mm.group(1), 0)
            # the bound is sometimes materialised in a register first (cmp eax, edx)
            mm = _MAX_REG_RE.search(previous)
            if mm and maximum is None:
                maximum = int(mm.group(1), 0)
            mm = _DEFAULT_RE.search(previous)
            if mm:
                default = int(mm.group(1), 16)
            mm = re.search(r"mov(?:zx|sx)? \w+, (?:word|dword) ptr \[\w+ \+ (0x[0-9a-f]+)\]", previous)
            if mm:
                field = int(mm.group(1), 16)
        if maximum is not None:
            found.append(dict(table=table, index=index, maximum=maximum, default=default, field=field))
    return found


def case_groups(table):
    """Case values grouped per switch body, ordered by the body's address.

    MSVC emits the bodies in source order, so this is the case order the source needs.
    The default body is left out.
    """
    img = image()
    bodies = {}
    for value in range(table["maximum"] + 1):
        slot = img.byte(table["index"] + value) if table["index"] else value
        target = img.dword(table["table"] + slot * 4)
        bodies.setdefault(target, []).append(value)
    return [bodies[target] for target in sorted(bodies) if target != table["default"]]


def state_table(asm):
    """The jump table of a unit state switch, or None.

    Prefers a dispatch on the state field; falls back to the only table in the function.
    """
    tables = jump_tables(asm)
    on_state = [t for t in tables if t["field"] == STATE_FIELD]
    if on_state:
        return on_state[0]
    return tables[0] if len(tables) == 1 else None


def function_addresses():
    """Map both the short and the fully qualified function name to its address."""
    addresses = {}
    for entry in common.resolver_index():
        addresses[entry["target"]] = entry["addr"]
        addresses.setdefault(entry["target"].split("::")[-1], entry["addr"])
    return addresses


def resolve(name):
    """Turn a function name or a 0x... address into an address."""
    if re.fullmatch(r"0x[0-9A-Fa-f]+", name):
        return int(name, 16)
    addresses = function_addresses()
    if name not in addresses:
        sys.exit("no resolver found for %s" % name)
    return addresses[name]


def main():
    names = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not names:
        sys.exit(__doc__)
    for name in names:
        address = resolve(name)
        asm = disassemble(address)
        print("###", name, "%#010x" % address)
        if "--jumptable" in sys.argv:
            for table in jump_tables(asm):
                print("table %#x index %s max %#x field %s" % (
                    table["table"], table["index"] and "%#x" % table["index"], table["maximum"],
                    table["field"] and "%#x" % table["field"]))
                for values in case_groups(table):
                    print("   ", values if len(values) < 12 else "default(%d values)" % len(values))
        else:
            print("\n".join(asm))


if __name__ == "__main__":
    main()
