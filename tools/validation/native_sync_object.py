import struct


def function(path, target):
    data = path.read_bytes()
    machine, _, _, sympos, nsymbols, optional, _ = struct.unpack_from("<HHIIIHH", data)
    assert machine == 0x14C and optional == 0
    strings = sympos + nsymbols * 18
    symbols = {}
    index = 0
    while index < nsymbols:
        name, value, section, _, _, aux = struct.unpack_from(
            "<8sIhHBB", data, sympos + index * 18
        )
        if name[:4] == b"\0" * 4:
            offset = strings + struct.unpack_from("<I", name, 4)[0]
            name = data[offset : data.index(b"\0", offset)]
        else:
            name = name.rstrip(b"\0")
        symbols[index] = (name.decode(), value, section)
        index += 1 + aux
    _, start, section = next(
        v
        for v in symbols.values()
        if v[0].startswith("?" + target + "@GameSynchronyState@")
    )
    header = 20 + (section - 1) * 40
    size, offset, relpos = struct.unpack_from("<III", data, header + 16)
    nrel = struct.unpack_from("<H", data, header + 32)[0]
    # /Gy places a single function in this section.
    assert start == 0
    code = bytearray(data[offset : offset + size])
    relocations = []
    for index in range(nrel):
        address, symbol, kind = struct.unpack_from("<IIH", data, relpos + index * 10)
        relocations.append((address, symbols[symbol][0], kind))
    return code, relocations
