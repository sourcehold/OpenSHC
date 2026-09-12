"""Differential original/compiled x86 sync routines. No live process access.

Only clock, send/queue delivery and the delegated unit-buffer hash are stubs.
Extreme checks translate verified struct offsets/addresses and unit capacity;
the OpenSHC C++ target remains Crusader, not a built Extreme DLL.
"""

from pathlib import Path
import argparse, hashlib, random, struct
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn import x86_const as reg
from native_sync_object import function

NAMES = ("checkGameSync", "sendPeriodicSyncMessages", "computeSomeHashOnUnitArray")
BASE_CODE = 0x4000000
STOP, CLOCK, STACK = 0x3DF1000, 0x3DF2000, 0x4108000


def check(variant, game, objects):
    extreme = variant == "Extreme"
    delta = 0x5C490 if extreme else 0
    base = 0x23547D8 if extreme else 0x191D768
    file = "Stronghold_Crusader_Extreme.exe" if extreme else "Stronghold Crusader.exe"
    expected_hash = (
        "55648e6b05d67d37a5773fe699bbb17a2d6ad4de1bb9dbded9a21caef82bd7fb"
        if extreme
        else "3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a"
    )
    assert hashlib.sha256((game / file).read_bytes()).hexdigest() == expected_hash, (
        "Unsupported original executable: " + file
    )
    pe = pefile.PE(str(game / file))
    image = pe.get_memory_mapped_image()
    entries = dict(
        zip(
            NAMES,
            (
                (0x48CC10, 0x48C860, 0x47F080)
                if extreme
                else (0x48CB00, 0x48C750, 0x47EEB0)
            ),
        )
    )
    queue = 0x489210 if extreme else 0x489100
    send126 = 0x4881F0 if extreme else 0x4880E0
    send0 = 0x487F40 if extreme else 0x487E30
    hasher = 0x46CF50 if extreme else 0x46CD30
    clock_import = 0x59E22C if extreme else 0x59E228
    units = 0x145CA28 if extreme else 0x1387F38
    direction = 0xEE283C if extreme else 0xEE23BC

    def original(a, n):
        return image[a - 0x400000 : a - 0x400000 + n]

    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x3E00000)
    for section in pe.sections:
        uc.mem_write(0x400000 + section.VirtualAddress, section.get_data())

    def put(a, v):
        uc.mem_write(a, struct.pack("<I", v & 0xFFFFFFFF))

    def get(a):
        return struct.unpack("<I", uc.mem_read(a, 4))[0]

    put(clock_import, CLOCK)
    for address, size in ((queue, 4), (send126, 0), (send0, 4), (hasher, 8)):
        uc.mem_write(address, b"\xc2" + struct.pack("<H", size))
    uc.mem_write(CLOCK, b"\xc3")
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    disassembler.detail = True
    codes = {}
    for name in NAMES:
        object_file = objects / (name + ".cpp.obj")
        if not object_file.exists():
            object_file = objects / (name + ".obj")
        code, relocs = function(object_file, name)
        for ins in disassembler.disasm(bytes(code), 0):
            if extreme and ins.disp_size == 4:
                disp = ins.disp
                if 0x7C85C <= disp <= 0x109FFF:
                    disp += delta
                elif -0x110000 <= disp <= -0x80000:
                    disp -= delta
                if disp != ins.disp:
                    struct.pack_into("<i", code, ins.address + ins.disp_offset, disp)
        if extreme and name == "computeSomeHashOnUnitArray":
            assert struct.unpack_from("<I", code, 6)[0] == 0x2C8E40
            struct.pack_into("<I", code, 6, 0xB23900)

        def bind(entry):
            result = bytearray(code)
            for offset, symbol, kind in relocs:
                addend = struct.unpack_from("<I", result, offset)[0]
                if kind == 6:
                    if "GameSynchronyState@" in symbol:
                        target = base
                    elif "UnitsState@" in symbol:
                        target = units
                    elif "DirectionAlgorithmState@" in symbol:
                        target = direction
                    elif symbol == "__imp__timeGetTime@0":
                        target = clock_import
                    else:
                        raise AssertionError(symbol)
                    struct.pack_into("<I", result, offset, target + addend)
                elif kind == 20:
                    target = next(
                        value
                        for key, value in {
                            "queueCommand": queue,
                            "sendSyncPacket126": send126,
                            "sendSomeMultiplayerSyncMessageWithType": send0,
                            "computeHash": hasher,
                        }.items()
                        if key in symbol
                    )
                    struct.pack_into("<i", result, offset, target - entry - offset - 4)
                else:
                    raise AssertionError((symbol, kind))
            return bytes(result)

        codes[name] = bind(BASE_CODE)
        assert bind(entries[name]) == original(entries[name], len(code)), (
            variant,
            name,
            "native bytes",
        )
        print(
            variant,
            name,
            len(code),
            "bytes match after native binding/layout translation",
        )

    offsets = {
        "halt": 0xB94,
        "pending": 0xBEC,
        "countdown": 0x7A870,
        "host": 0x790,
        "hashCountdown": 0x1092AC + delta,
        "delay": 0x109EE8 + delta,
        "timer126": 0x109ED0 + delta,
        "timer0": 0x109ED4 + delta,
    }
    handles, hashes, times, excluded = 0x6A8, 0x7A898, 0x7A8BC, 0x106DF8 + delta
    ack, status = 0x101A8C + delta, 0x101AB0 + delta
    writes = []
    calls = []
    current = {}

    def on_write(machine, access, address, size, value, data):
        if not STACK - 0x1000 <= address < STACK + 0x1000:
            writes.append((address, size, value & ((1 << (8 * size)) - 1)))

    uc.hook_add(UC_HOOK_MEM_WRITE, on_write)

    def observe(machine, address, size, data):
        if address == STOP:
            machine.emu_stop()
            return
        if address == CLOCK:
            machine.reg_write(reg.UC_X86_REG_EAX, current.get("now", 0))
            return
        this = current["this"]
        if address == queue:
            calls.append(
                (
                    "queue",
                    machine.reg_read(reg.UC_X86_REG_ECX),
                    get(machine.reg_read(reg.UC_X86_REG_ESP) + 4),
                    get(this + offsets["pending"]),
                    get(this + offsets["countdown"]),
                    get(this + offsets["delay"]),
                )
            )
        if address == send126:
            calls.append(
                (
                    "126",
                    machine.reg_read(reg.UC_X86_REG_ECX),
                    get(this + offsets["timer126"]),
                )
            )
            if current.get("mutate") == 1:
                put(this + offsets["timer0"], current["now"])
        if address == send0:
            calls.append(
                (
                    "0",
                    machine.reg_read(reg.UC_X86_REG_ECX),
                    get(machine.reg_read(reg.UC_X86_REG_ESP) + 4),
                    get(this + offsets["timer0"]),
                )
            )
            if current.get("mutate") == 2:
                put(this + offsets["countdown"], 2)
        if address == hasher:
            sp = machine.reg_read(reg.UC_X86_REG_ESP)
            calls.append(
                ("hash", machine.reg_read(reg.UC_X86_REG_ECX), get(sp + 4), get(sp + 8))
            )
            machine.reg_write(reg.UC_X86_REG_EAX, current["return"])

    for address in (STOP, CLOCK, queue, send126, send0, hasher):
        uc.hook_add(UC_HOOK_CODE, observe, begin=address, end=address)

    def run(name, values, compiled):
        current.clear()
        current.update(values)
        this = values.get("this", base)
        current["this"] = this
        fields = {key: values.get(key, 0) for key in offsets}
        fields.update(halt=37, delay=47)
        for key, value in fields.items():
            put(this + offsets[key], value)
        put(base + offsets["host"], values.get("globalHost", 1))
        for i in range(9):
            for start, key, default in (
                (handles, "handles", -1),
                (hashes, "hashes", 123),
                (times, "times", 64),
                (excluded, "excluded", 0),
            ):
                put(this + start + i * 4, values.get(key, [default] * 9)[i])
            put(this + ack + i * 4, 100 + i)
            put(this + status + i * 4, 200 + i)
        writes.clear()
        calls.clear()
        entry = BASE_CODE if compiled else entries[name]
        if compiled:
            uc.mem_write(BASE_CODE, codes[name])
            uc.ctl_remove_cache(BASE_CODE, BASE_CODE + len(codes[name]))
        registers = {
            "EBX": 0x1111,
            "ESI": 0x2222,
            "EDI": 0x3333,
            "EBP": 0x4444,
            "ECX": this,
            "ESP": STACK,
            "EFLAGS": 0x202,
        }
        for key, value in registers.items():
            uc.reg_write(getattr(reg, "UC_X86_REG_" + key), value)
        put(STACK, STOP)
        uc.emu_start(entry, 0, count=10000)
        assert uc.reg_read(reg.UC_X86_REG_EIP) == STOP, (variant, name, values)
        assert uc.reg_read(reg.UC_X86_REG_ESP) == STACK + 4
        for key in ("EBX", "ESI", "EDI", "EBP"):
            assert uc.reg_read(getattr(reg, "UC_X86_REG_" + key)) == registers[key]
        result = (calls[:], {a: (s, v) for a, s, v in writes})
        if name == "computeSomeHashOnUnitArray":
            result += (uc.reg_read(reg.UC_X86_REG_EAX),)
        return result

    def compare(name, values):
        expected = run(name, values, False)
        actual = run(name, values, True)
        assert expected == actual, (variant, name, values, expected, actual)

    count = 0
    for first in range(1, 9):
        for second in range(1, 9):
            if first == second:
                continue
            for issue in (
                "equal",
                "hash",
                "time",
                "zero",
                "early",
                "excluded",
                "absent",
            ):
                for countdown in (-1, 0, 5):
                    values = {
                        "handles": [-1] * 9,
                        "hashes": [123] * 9,
                        "times": [64] * 9,
                        "excluded": [0] * 9,
                        "countdown": countdown,
                    }
                    values["handles"][first] = 11
                    values["handles"][second] = 22
                    if issue == "hash":
                        values["hashes"][second] = 0x80000001
                    if issue == "time":
                        values["hashes"][second] = 456
                        values["times"][second] = 65
                    if issue == "zero":
                        values["hashes"][second] = 0
                    if issue == "early":
                        values["times"][second] = 9
                    if issue == "excluded":
                        values["excluded"][second] = 1
                        values["hashes"][second] = 456
                    if issue == "absent":
                        values["handles"][second] = -1
                        values["hashes"][second] = 456
                    compare("checkGameSync", values)
                    count += 1
    rng = random.Random(34141)
    for i in range(1200):
        values = {
            "handles": [rng.choice([-1, 0, 17]) for _ in range(9)],
            "hashes": [
                rng.choice([0, 11, 22, 0x80000000, 0xFFFFFFFF]) for _ in range(9)
            ],
            "times": [rng.choice([0, 9, 10, 64, 65, 0xFFFFFFFF]) for _ in range(9)],
            "excluded": [rng.randrange(2) for _ in range(9)],
            "countdown": rng.choice([-1, 0, 5]),
            "hashCountdown": rng.choice([0, 0, 0, 1, 0xFFFFFFFF]),
            "pending": rng.choice([0, 0, 1]),
            "globalHost": rng.randrange(2),
            "host": rng.randrange(2),
            "this": base if i % 2 else 0x3000000,
        }
        compare("checkGameSync", values)
        count += 1
    print(
        variant,
        count,
        "host sync comparison cases, including independent this/global state",
    )
    count = 0
    for now in (17, 10000, 0xFFFFFFF0):
        for elapsed126 in (0, 179, 180, 1800, 1801, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
            for elapsed0 in (
                0,
                179,
                180,
                1800,
                1801,
                0x7FFFFFFF,
                0x80000000,
                0xFFFFFFFF,
            ):
                for countdown in (-1, 0, 1, 5):
                    for mutate in (0, 1, 2):
                        compare(
                            "sendPeriodicSyncMessages",
                            {
                                "now": now,
                                "timer126": now - elapsed126,
                                "timer0": now - elapsed0,
                                "countdown": countdown,
                                "mutate": mutate,
                            },
                        )
                        count += 1
    print(
        variant, count, "periodic signed-clock/threshold/wrap/callback mutation cases"
    )
    for value in (0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
        for this in (base, 0x3000000):
            compare("computeSomeHashOnUnitArray", {"return": value, "this": this})
    print(variant, "10 unit-buffer hash delegation/return/ABI cases")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "game", type=Path, help="Directory containing both original 1.41 executables"
    )
    parser.add_argument(
        "objects",
        type=Path,
        help="Directory containing the three MSVC x86 object files",
    )
    args = parser.parse_args()
    for variant in ("SHC", "Extreme"):
        check(variant, args.game, args.objects)
