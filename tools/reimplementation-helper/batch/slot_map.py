"""Compare a function's stack frame against the original's, without reccmp.

usage: slot_map.py FILE.cpp [--orig-only] [--refs] [--end=0xADDR]

Checking the frame first is worth it because the frame is the one part of the output that is
decided by information the source controls directly - which locals exist, how big they are and
how often each is used - and because reccmp's percentage actively misleads here. Adding a local
shifts every `[esp + N]` displacement in the function, so reccmp scores all of them as
mismatches until the layout happens to line up: on `renderDebugDataAiInfo`, adding the two
locals the original demonstrably has moved the frame from 0x3f8 to exactly 0x400 and the
instruction-mix delta from 13 to 3, while the percentage *fell* from 68.4 to 67.5. Frame first,
then the instruction mix, and reccmp only to confirm at the end.

What each side gives:

* ours - MSVC's `/FA` listing states the frame outright, one line per slot with its name, its
  offset from the entry `esp` and its size:

      _this$GSCopy$ = -1016      ; size = 4
      _playerID$ = -1012         ; size = 4
      _text$ = -1004             ; size = 1000
      __$ArrayPad$ = -4          ; size = 4

* the original - has to be inferred from the disassembly. Every stack reference is
  `[esp + displacement]` where the displacement depends on how far `esp` has been pushed down
  at that instruction, so the slot it names is `displacement - depth`, with `depth` tracked
  across `push`/`pop`/`sub esp`/`add esp` from the function entry. That recovers the same
  entry-relative offsets the listing prints, which makes the two directly comparable.

Slot *sizes* on the original side cannot be read off, only bounded: a 1000-byte buffer is
touched once through `lea` at its base, so its size shows up as the gap to the next slot that
is referenced. The report prints the gap as `span` and the widest observed access as `acc`,
and never pretends the two are the same thing.

Reference counts matter as much as the offsets, and there are two regimes (decoded from
c2.dll, see tools/compiler-internals/msvc-backend.md "The slot tiebreak, decoded"):

* frame > 0x80 bytes, or a /GS buffer: `QSortColors` sorts the slots by the class byte, then by
  `weight * 1000 / size` descending. The `key` column prints that key.
* otherwise the sort is SKIPPED and the slot order is c2's element list as built: size
  ascending, then reference count descending, and among equal counts the local whose LAST
  reference comes first in the tuple stream gets the higher address. Declaration order is not in
  the rule. An `__asm` block counts each local once per operand set (def-set, use-list, def-set
  again), and its def-set is iterated in name-hash order, so for asm-written locals the name
  itself is the tiebreak. The `key` column then prints the reference count, and
  `tools/compiler-internals/slot_probe.py` shows the exact reference sequence.

Either way a local in the wrong place usually means our reference count differs from the
original's. `--refs` lists every referencing address per slot. The report names the regime.

A `?` row on either side is a slot that side does not have. Those are the actionable rows: a
`?` under ours is a local the original has and we do not.

Needs capstone and a configured build directory; no build and no reccmp run.
"""

import collections
import os
import struct
import re
import sys

import asm_streams
import common
import orig_body

LISTING = common.ROOT / common.TMP / 'quick' / 'x.asm'
SLOT_DECL = re.compile(r'^(\S+) = (-?\d+)\s*;\s*size = (\d+)\s*$')
# `dword ptr [esp + 0x3f8]`, `[esp]`, and the `lea reg, [esp + N]` form with no size prefix
ESP_REF = re.compile(r'(?:(\w+) ptr )?\[esp(?:\s*([+-])\s*(0x[0-9a-f]+|\d+))?\]')
ORIG_ONLY = False
SHOW_REFS = False
WIDTH = {'byte': 1, 'word': 2, 'dword': 4, 'qword': 8, 'tbyte': 10, 'xmmword': 16}


def ours(path):
    """(frame_size, [(offset, size, refs, name)]) from the /FA listing."""
    text = common.read_text(path)
    m = re.search(r'FUNCTION: STRONGHOLDCRUSADER[^\n]*\n[^\n(]*?(\w+)::(\w+)\(', text)
    if not m:
        raise ValueError('%s has no `// FUNCTION:` marker followed by a definition' % path)
    cls, name = m.groups()
    asm_streams.streams(path, keep_slots=True)       # produces the listing
    listing = common.read_text(LISTING).splitlines()
    pat = re.compile(r'^\?%s@%s@\S* PROC' % (re.escape(name), re.escape(cls)))
    start = next((i for i, l in enumerate(listing) if pat.match(l)), None)
    if start is None:
        raise ValueError('no code emitted for %s::%s (inlined, or named differently)' % (cls, name))
    # the slot table is the run of `name = N ; size = M` lines just above the PROC line
    slots = []
    i = start - 1
    while i >= 0:
        d = SLOT_DECL.match(listing[i].replace('\t', ' ').strip())
        if d:
            slots.append((int(d.group(2)), int(d.group(3)), d.group(1)))
        elif slots:
            break
        i -= 1
    end = next(i for i in range(start, len(listing)) if ' ENDP' in listing[i])
    body = '\n'.join(listing[start:end])
    frame = 0
    f = re.search(r'\n\tsub\tesp, (\d+)', body)
    if f:
        frame = int(f.group(1))
    gs = '___security_cookie' in body
    out = []
    for off, size, nm in sorted(slots):
        if off >= 8:
            continue                   # +8 and up are the incoming arguments, not the frame
        refs = len(re.findall(r'\b%s\[e(?:sp|bp)' % re.escape(nm), body))
        if refs == 0:
            # MSVC emits slot symbols it then never uses - an unspilled `_this$`, EH
            # bookkeeping. The original side can only ever show slots that are actually
            # referenced, so keeping these invents a difference: in
            # `clearPlayerDataInformationChunk`, which matches 100%, three such symbols
            # made a frameless function look three slots too big.
            continue
        out.append((off, size, refs, nm))
    return frame, out, gs


def _imm(text):
    text = text.strip()
    try:
        return int(text, 16) if text.lower().startswith('0x') else int(text)
    except ValueError:
        return None


_POPPED = {}


def popped(image, target):
    """How many bytes of arguments the function at `target` pops on return.

    A `__thiscall` or `__stdcall` callee cleans up its own arguments, so `esp` rises across
    the call by an amount that is nowhere visible at the call site - most of the calls in a
    rendering function are of that kind, with nine pushes and no `add esp` afterwards. Reading
    the callee's `ret N` is the only way to know, and getting it wrong desynchronises every
    stack offset after the first call.
    """
    if target in _POPPED:
        return _POPPED[target]
    _POPPED[target] = 0                  # guard against a recursive thunk chain
    try:
        stream = orig_body.disassemble(target, target + 0x40, image)
    except Exception:
        return 0
    for _a, mnemonic, ops in stream:
        if mnemonic == 'jmp':             # an import thunk; follow it once
            t = _imm(ops)
            _POPPED[target] = popped(image, t) if t is not None else 0
            return _POPPED[target]
        if mnemonic == 'ret':
            _POPPED[target] = _imm(ops) or 0
            return _POPPED[target]
    # no `ret` in the first 0x40 bytes: disassemble the whole body and take its first one
    try:
        for _a, mnemonic, ops in orig_body.disassemble(target, None, image):
            if mnemonic == 'ret':
                _POPPED[target] = _imm(ops) or 0
                break
    except Exception:
        pass
    return _POPPED[target]


_TABLE = re.compile(r'\[\w+\*4 \+ (0x[0-9a-f]+)\]')


def _jump_table(image, ops, lo, hi):
    """Targets of a switch's `jmp dword ptr [reg*4 + TABLE]`.

    MSVC emits the table just past the function's last instruction, and for a sparse switch
    puts a byte index table after it, so the dword entries are followed only while they point
    back inside the body - the first value that does not is the next table's data. On
    `addUnitToSmallestBehaviourTypeTribe` that yields exactly five case targets and stops on
    `0x04040400`, which is the byte table.
    """
    m = _TABLE.search(ops)
    if not m:
        return []
    base = int(m.group(1), 16)
    off = image.offset(base)
    if off is None:
        return []
    out = []
    for i in range(256):
        if off + 4 * i + 4 > len(image.data):
            break
        t = struct.unpack_from('<I', image.data, off + 4 * i)[0]
        if not (lo <= t <= hi):
            break
        out.append(t)
    return out


def _delta(image, mnemonic, ops, unknown_calls, addr):
    """How much this instruction lowers `esp` (negative means it raises it)."""
    if mnemonic in ('push', 'pushfd'):
        return 4
    if mnemonic in ('pop', 'popfd'):
        return -4
    if mnemonic in ('sub', 'add') and ops.replace(' ', '').startswith('esp,'):
        k = _imm(ops.split(',', 1)[1])
        if k is None:
            return 0
        return k if mnemonic == 'sub' else -k
    if mnemonic == 'call':
        t = _imm(ops)
        if t is None:
            # an indirect call through a register or vtable slot: the convention is not
            # readable from here, so say so rather than silently assuming cdecl
            unknown_calls.append(addr)
            return 0
        return -popped(image, t)
    return 0


def original(address, end=None):
    """(frame_size, [(offset, span, acc_width, refs, addrs)]) inferred from the disassembly.

    `esp` depth cannot be tracked by walking the listing top to bottom: both arms of an
    `if`/`else` push their own arguments before a shared call, so a straight-line walk counts
    both and drifts further out with every branch. Depth is propagated over the control-flow
    graph instead, which also makes a genuine disagreement at a join point detectable.
    """
    image = orig_body.Image()
    stream = orig_body.disassemble(address, end, image)
    idx = dict((a, i) for i, (a, _m, _o) in enumerate(stream))
    lo, hi = stream[0][0], stream[-1][0]
    unknown_calls = []
    deltas, succs = [], []
    for i, (addr, mnemonic, ops) in enumerate(stream):
        deltas.append(_delta(image, mnemonic, ops, unknown_calls, addr))
        out = []
        target = _imm(ops) if mnemonic.startswith('j') else None
        if target is not None and lo <= target <= hi and target in idx:
            out.append(idx[target])
        elif mnemonic == 'jmp':
            # a switch: `jmp dword ptr [reg*4 + 0x4ccedc]`. Without following it, every case
            # body is unreachable and its stack references go uncounted - 52 instructions of
            # `addUnitToSmallestBehaviourTypeTribe`, which is most of the function.
            for t in _jump_table(image, ops, lo, hi):
                if t in idx:
                    out.append(idx[t])
        if mnemonic != 'jmp' and mnemonic != 'ret' and i + 1 < len(stream):
            out.append(i + 1)
        succs.append(out)

    depth = [None] * len(stream)
    depth[0] = 0
    work, conflicts = [0], []
    while work:
        i = work.pop()
        d = depth[i] + deltas[i]
        for j in succs[i]:
            if depth[j] is None:
                depth[j] = d
                work.append(j)
            elif depth[j] != d:
                conflicts.append((stream[j][0], depth[j], d))

    # the prologue allocation is the first `sub esp, imm`, which is not always the first
    # instruction: `planToBuyWhenLowOnResourceAndSnoozeBuildings` reads an argument into eax
    # first, and requiring instruction 0 reported its frame as 0 while its ten slots were
    # plainly there. Stop at the first transfer of control, so a `sub esp` that belongs to a
    # call's argument setup is never mistaken for the frame.
    frame = 0
    for _a, mnemonic, ops in stream[:12]:
        if mnemonic in ('call', 'ret', 'jmp') or mnemonic.startswith('j'):
            break
        if mnemonic == 'sub' and ops.replace(' ', '').startswith('esp,'):
            frame = _imm(ops.split(',', 1)[1]) or 0
            break

    gs = any('0xb94220' in ops for _a, _m, ops in stream)
    hits = collections.defaultdict(lambda: {'refs': 0, 'acc': 0, 'addrs': []})
    unreached = 0
    for i, (addr, mnemonic, ops) in enumerate(stream):
        if depth[i] is None:
            unreached += 1
            continue
        if orig_body.is_padding(mnemonic, ops):
            continue                     # `lea esp, [esp]` is filler, not a stack reference
        for width, sign, num in ESP_REF.findall(ops):
            disp = 0 if not num else (int(num, 16) if num.startswith('0x') else int(num))
            if sign == '-':
                disp = -disp
            h = hits[disp - depth[i]]
            h['refs'] += 1
            h['acc'] = max(h['acc'], WIDTH.get(width, 0))
            h['addrs'].append(addr)
    # at or above the entry esp sit the return address and the incoming arguments, which are
    # the caller's, not this frame's. Drop them BEFORE measuring spans, or the last local's
    # span is the gap to the return address rather than its own size.
    #
    # Below -frame is impossible: the prologue allocated exactly `frame` bytes, so an offset
    # past that is proof the depth tracking drifted rather than a slot. `aiCreateSiegeUnits`
    # produced one at -52 against a 0x30 frame, which made it look a slot bigger than ours;
    # it is counted separately and reported, not listed as if it were real.
    impossible = sorted(o for o in hits if o < 0 and frame and o < -frame)
    offs = [o for o in sorted(hits) if o < 0 and not (frame and o < -frame)]
    out = []
    for i, off in enumerate(offs):
        span = (offs[i + 1] - off) if i + 1 < len(offs) else None
        h = hits[off]
        out.append((off, span, h['acc'], h['refs'], h['addrs']))
    return frame, out, {'conflicts': conflicts, 'unknown_calls': unknown_calls,
                        'unreached': unreached, 'impossible': impossible, 'gs': gs}


def regime(frame, gs):
    """'sorted' when ColorStackElements runs QSortColors (frame over 0x80 bytes, or a /GS buffer),
    else 'list-order': the element list as AddStackElement built it is the slot order."""
    return 'sorted' if (frame > 0x80 or gs) else 'list-order'


def key(refs, size, mode='sorted'):
    """The ordering key per regime: StkColorCmp's weight * 1000 / size when the sort runs, the
    bare reference count (the list is weight-descending) when it does not."""
    if mode != 'sorted':
        return refs
    return (refs * 1000 // size) if size else 0


def main():
    # parsed here, not at import: the other tools import this module for `original()` and
    # `ours()`, and a module-level sys.exit turns that into an abrupt exit with a usage dump
    global ORIG_ONLY, SHOW_REFS
    ORIG_ONLY = '--orig-only' in sys.argv
    SHOW_REFS = '--refs' in sys.argv
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    if not args:
        sys.exit(__doc__)
    path = args[0]
    address = orig_body.address_of(path)
    # --end 0xADDR: the original's true end when orig_body's detection stops early. A function
    # whose switch cases sit after the detected end (processHelpRichTextTokens: 703 instructions
    # unreached, its jump table at the real end) needs this or its slot counts are a fraction.
    end = None
    for a in sys.argv[1:]:
        if a.startswith('--end='):
            end = int(a.split('=', 1)[1], 16)
    o_frame, o_slots, trouble = original(address, end)
    for addr, had, got in trouble['conflicts'][:3]:
        print('WARNING: two paths reach %#x with different esp depths (%+d and %+d), so the'
              % (addr, had, got))
        print('         offsets below may be wrong. Usually an indirect call whose argument')
        print('         cleanup could not be read, or a tail-merged block.')
    if trouble['unknown_calls']:
        print('NOTE: %d indirect call(s), e.g. %#x - the callee pops an unknown number of'
              % (len(trouble['unknown_calls']), trouble['unknown_calls'][0]))
        print('      argument bytes, assumed 0. Offsets after it are suspect.')
    if trouble.get('impossible'):
        print('WARNING: %d reference(s) landed below the frame (%s), which cannot be a slot -'
              % (len(trouble['impossible']),
                 ', '.join(str(o) for o in trouble['impossible'][:4])))
        print('         the depth tracking drifted. They are excluded, but every offset below')
        print('         is suspect; do not read a slot-count difference as a real defect.')
    if trouble['unreached']:
        print('NOTE: %d instruction(s) were not reached from the entry, so their stack'
              % trouble['unreached'])
        print('      references are not counted (jump table or a misdetected function end).')
    if trouble['conflicts'] or trouble['unknown_calls'] or trouble['unreached']:
        print('')
    print('frame   original %#x   ours %s'
          % (o_frame, '(not compared)' if ORIG_ONLY else ''), end='')
    if ORIG_ONLY:
        print('')
        for off, span, acc, refs, addrs in o_slots:
            print('  %6d  span %-5s acc %-2s refs %-3d' % (off, span, acc or '?', refs))
        return
    u_frame, u_slots, u_gs = ours(path)
    print('%#x   (%+d)' % (u_frame, u_frame - o_frame))
    mode = regime(o_frame, trouble.get('gs', False))
    u_mode = regime(u_frame, u_gs)
    if mode == 'sorted':
        print('regime  sorted: frame > 0x80 or /GS buffer, so slots follow weight*1000/size (the `key` column)')
    else:
        print('regime  list-order: frame <= 0x80 and no /GS buffer, so QSortColors is skipped - slots follow')
        print('        reference count (the `key` column), ties by whose LAST reference comes first;')
        print('        for asm-written locals that is the name-hash order of the def-set (slot_probe.py)')
    if u_mode != mode:
        print('WARNING: ours is in the %s regime (frame %#x, cookie %s) while the original is %s - the'
              % (u_mode, u_frame, 'yes' if u_gs else 'no', mode))
        print('         orders are not comparable until the frame size / GS state agrees')
    print('')
    # pair the two layouts in offset order; both are entry-relative, so a constant shift means
    # the layout is right and only the frame size differs
    print('%-28s | %s' % ('ORIGINAL (inferred)', 'OURS (from the /FA listing)'))
    print('%6s %6s %4s %5s %6s | %6s %6s %5s %6s  %s'
          % ('off', 'span', 'acc', 'refs', 'key', 'off', 'size', 'refs', 'key', 'name'))
    # both frames end at the same place - the security cookie and the return address anchor the
    # high end - so pad the shorter column at the FRONT. Aligning from the top instead would
    # shift every row and make one missing local look like every slot being wrong.
    n = max(len(o_slots), len(u_slots))
    o_pad, u_pad = n - len(o_slots), n - len(u_slots)
    for i in range(n):
        if i >= o_pad:
            off, span, acc, refs, _a = o_slots[i - o_pad]
            size = span if span else (acc or 4)
            left = '%6d %6s %4s %5d %6d' % (off, span if span else '-', acc or '?', refs,
                                            key(refs, size, mode))
        else:
            left = '%6s %6s %4s %5s %6s' % ('?', '', '', '', '')
        if i >= u_pad:
            uoff, usize, urefs, nm = u_slots[i - u_pad]
            right = '%6d %6d %5d %6d  %s' % (uoff, usize, urefs, key(urefs, usize, mode), nm)
        else:
            right = '%6s %6s %5s %6s  %s' % ('?', '', '', '', '<-- a local we do not have')
        print('%s | %s' % (left, right))
    print('')
    print('  %d slot(s) on the original side, %d on ours.' % (len(o_slots), len(u_slots)))
    if u_frame != o_frame:
        d = o_frame - u_frame
        print('  Frame differs by %+d bytes, so %s %d dword-sized local(s).'
              % (-d, 'we are missing about' if d > 0 else 'we have about', abs(d) // 4))
        print('  A frame that is too small is strong evidence of a missing local. Too large can')
        print('  be either a surplus local or a spill, so it is weaker evidence.')
    else:
        print('  Frame sizes agree, so the set of locals is probably right and what is left is')
        if mode == 'sorted':
            print('  their ORDER - compare the `key` columns, since that is what the sort uses.')
        else:
            print('  their ORDER - compare the reference counts; equal counts are ordered by the position')
            print('  of the LAST reference, which slot_probe.py prints for each local.')
    if SHOW_REFS:
        print('')
        for off, _span, _acc, refs, addrs in o_slots:
            print('  original %6d  %d refs: %s'
                  % (off, refs, ' '.join('%08x' % a for a in addrs[:14])))


if __name__ == '__main__':
    main()
