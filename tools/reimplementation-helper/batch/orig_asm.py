"""Print the ORIGINAL instruction stream of one function from the current reccmp diff.

`reccmp_report.py diff NAME` shows an interleaved diff, which is what you want while closing a
small gap. It is the wrong tool when you need to read the original on its own:

  * the diff only covers instructions reccmp chose to align, so long functions come back truncated;
  * reconstructing control flow (a switch, a loop nest, a hand-written asm block) needs the
    original's own jump targets and fall-through order, which the interleaving hides.

This prints just the original side, in address order, so it can be read or grepped like a listing.
It needs no Ghidra connection - it reuses `reccmp/dll/diff.json` from the last
`reccmp_report.py --run` - so it also works when the Ghidra MCP server is down.

usage:
    orig_asm.py NAME [--both]        # NAME matches the end of the reccmp symbol name
    orig_asm.py NAME --stats         # instruction count and the tells for a handwritten original

`--both` also prints the instructions reccmp matched, marked "=", so the output is the full original
body rather than only the parts that differ.

`--stats` reports the signals that decide how a function has to be reimplemented at all:
  * "mov reg, 0"        - no compiler materialises zero that way; the block is handwritten assembly
                          and belongs in an __asm block (see AGENTS.md and NeighbourFlagsAsm.hpp).
  * frame pointer       - "push ebp / mov ebp, esp" with locals addressed off ebp means the original
                          was built without optimisation; the reimplementation needs
                          #pragma optimize("", off). The same prologue with "and esp, -N" is only
                          /O2 realigning the stack for a large local, and is NOT an /Od tell.
  * "sub esp, N"        - the frame size. Matching it exactly is usually the single biggest win for
                          an unoptimised function, because every local displacement shifts otherwise.
  * "jmp dword ptr"     - a jump table: Ghidra often renders the dispatch as a call through an
                          unnamed pointer array and drops the arms, so the switch must be rebuilt
                          from the byte/jump tables rather than restyled from the decompiler output.
"""

import io
import json
import re
import sys

import common

USAGE = 'usage: orig_asm.py NAME [--both|--stats]'


def find(node, name):
    """Locate the diff entry whose symbol name ends with `name`."""
    if isinstance(node, dict):
        if str(node.get('name', '')).endswith(name):
            return node
        for value in node.values():
            hit = find(value, name)
            if hit:
                return hit
    elif isinstance(node, list):
        for value in node:
            hit = find(value, name)
            if hit:
                return hit
    return None


def instructions(entry, both):
    """Yield (address, text, matched) for the original side, in address order.

    The payload is a list of hunks; each hunk is [header, [group, ...]] and each group is
    {"orig"|"both"|"recomp": [[address, text] or [address, text, recomp_address], ...]}.
    """
    out = []

    def walk(node):
        if isinstance(node, dict):
            for key in ('orig', 'both'):
                if key not in node:
                    continue
                if key == 'both' and not both:
                    continue
                for row in node[key]:
                    if not (isinstance(row, (list, tuple)) and len(row) >= 2):
                        continue
                    # reccmp leaves the address empty on rows it synthesised (padding,
                    # and the blank line it puts between hunks); keep them in order by
                    # reusing the previous address rather than dropping the instruction.
                    try:
                        address = int(row[0], 16)
                    except (TypeError, ValueError):
                        address = out[-1][0] if out else 0
                    out.append((address, row[1].rstrip(), key == 'both'))
        elif isinstance(node, list):
            for item in node:
                walk(item)

    walk(entry['diff'])
    out.sort(key=lambda row: row[0])
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    flags = {a for a in sys.argv[1:] if a.startswith('--')}
    if len(args) != 1 or flags - {'--both', '--stats'}:
        sys.exit(USAGE)
    name = args[0]

    if not common.DIFF_JSON.exists():
        sys.exit('%s not found; run reccmp_report.py --run pct first' % common.DIFF_JSON)
    entry = find(json.load(io.open(str(common.DIFF_JSON), encoding='utf-8')), name)
    if entry is None:
        sys.exit('no reccmp entry whose name ends with %r' % name)

    rows = instructions(entry, both='--both' in flags or '--stats' in flags)
    print('# %s  %s  %.2f%%' % (entry['name'], entry['address'], float(entry['matching']) * 100))

    if '--stats' in flags:
        text = '\n'.join(row[1] for row in rows)
        zero = re.findall(r'\bmov e[a-z]{2}, 0\b', text)
        # `push ebp / mov ebp, esp` alone is not an /Od tell: /O2 emits the same pair when a
        # function realigns the stack for a large local (`and esp, -N`, usually with __chkstk),
        # and there the locals still live at [esp + N]. A real /Od frame addresses them off ebp.
        prologue = bool(re.search(r'\bpush ebp\b', text)) and bool(re.search(r'\bmov ebp, esp\b', text))
        realigned = bool(re.search(r'\band esp, 0x[0-9a-f]+\b', text))
        ebp_locals = bool(re.search(r'\[ebp - 0x[0-9a-f]+\]', text))
        frame = prologue and ebp_locals and not realigned
        stack = re.findall(r'\bsub esp, (0x[0-9a-f]+|\d+)\b', text)
        tables = re.findall(r'\bjmp dword ptr\b', text)
        print('# instructions seen: %d (matched and differing)' % len(rows))
        print('# mov reg, 0        : %d%s' % (len(zero), '   <- handwritten assembly' if zero else ''))
        print('# frame pointer     : %s%s' % (frame, '   <- built /Od; use #pragma optimize' if frame else ''))
        print('# frame size        : %s' % (', '.join(stack) if stack else 'none'))
        print('# jump tables       : %d%s' % (len(tables), '   <- rebuild the switch by hand' if tables else ''))
        return

    for address, text, matched in rows:
        print('%08x %s %s' % (address, '=' if matched else '-', text))


if __name__ == '__main__':
    main()
