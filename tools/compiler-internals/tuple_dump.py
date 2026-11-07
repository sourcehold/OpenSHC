"""Print one function's code the way c2.dll holds it, at each stage of compilation.

usage: tuple_dump.py FILE.cpp --name FUNC                 every phase, side by side
       tuple_dump.py FILE.cpp --name FUNC --at P[,P...]   only these phases (names below)
       tuple_dump.py FILE.cpp --name FUNC --diff A B      unified diff of two phases
       tuple_dump.py FILE.cpp --name FUNC --raw           the raw field dump as well
       tuple_dump.py --tables                             refresh c2_tables.json from c2.dll

Why: `quick_diff.py` and reccmp show what the compiler *ended up with*. When the final code
differs from the original, the question is which pass made the choice - did the front end
already emit the blocks in that order, did the lowerer pick `[edx+ecx]` over `[ecx+edx]`, did
the register allocator spill the local, or did the late tail-merge fold the two return blocks?
This prints the function after every phase, so the first phase where the stream disagrees with
the original is the one to read about in msvc-backend.md.

Phases (in compile order; `--at` takes any of these names):

    initial      dop2_InitialOptsAndSetup   front-end tuples, before inlining and global opts
    prelower     dop2_PreLowerGlobalOpts     after inlining, before global opts
    codegen      dop2_Codegen                after global opts (CSE, hoisting) - still IL
    postlower    dop2_PostLowerPreRegAlloc   lowered to x86 tuples, pseudo-registers
    regalloc     dop2_GlobalRegAlloc         just before register allocation
    update       dop2_CodegenUpdate          after register allocation
    postcodegen  dop2_PostCodegenFlowOpts
    finish       dop2_CodegenFinish
    final        dop2_FinalFlowOpts          before tail merge / code motion
    preencode    dop2_PreEncode              the final stream, what the listing prints
    color        ColorStackElements          when stack slots are laid out

The dump is c2's own data, decoded with the layouts the listing writer (`MdPrintInstr`,
`MdPrintOperand` in P2/x86/mdlist.c) uses - see msvc-backend.md, "Tuples and operands, as the
listing writer reads them". Opcode names come from c2.dll's own tables (`_Opcode_name` for
x86 opcodes below 0x274, the IL table at 0x10cebda8 above it), cached in `c2_tables.json`.

Reading the output:

    BLK 3  preds=1,2  succs=5
      0x0314a2c0  mov       edi, eax                 ; kind=d
      0x0314a300  cmp       dword ptr _x$[esp], 0
      0x0314a340  jne       L0x0314b000              ; kind=12 (conditional branch)
      0x0314a380  OPCALL    ?foo@@YAXXZ(t12, ecx)    ; IL tuple, before lowering

Pseudo-registers print as `t<n>`; a local prints as `_name$[esp+off]` or just `_name$` while
it is still a candidate; `(temp)` is a compiler temporary with no source name. Lines with
kind 0x17-0x1b are block/label/entry/exit pseudo tuples and are shown dimmed as `.label` etc.

The function is found by its mangled name at `dop2_InitialOptsAndSetup` (the first phase that
sees it), so it works for free functions too. Each run is one compile of FILE.cpp under cdb,
about 20-60 s.
"""

import c2base
import json
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import slot_probe
from slot_probe import EQ, NL, out, run

Q = chr(34)          # a plain quote: script files run with $$>< are not nested in a bp command
N = chr(92) + 'n'    # the two characters \ n, which .printf turns into a newline

HERE = os.path.dirname(os.path.abspath(__file__))
TABLES = os.path.join(HERE, 'c2_tables.json')

# c2.dll (14.00.50727.762, image base 0x10b00000) - names from c2.pdb
PHASES = [
    ('initial', '0x10c06890', 'dop2_InitialOptsAndSetup'),
    ('prelower', '0x10c06cc0', 'dop2_PreLowerGlobalOpts'),
    ('codegen', '0x10c06fa0', 'dop2_Codegen'),
    ('postlower', '0x10c072b0', 'dop2_PostLowerPreRegAllocGlobalOpts'),
    ('regalloc', '0x10c07350', 'dop2_GlobalRegAlloc'),
    ('update', '0x10c07400', 'dop2_CodegenUpdate'),
    ('postcodegen', '0x10c07630', 'dop2_PostCodegenFlowOpts'),
    ('finish', '0x10c07690', 'dop2_CodegenFinish'),
    ('final', '0x10c07780', 'dop2_FinalFlowOpts'),
    ('preencode', '0x10c07850', 'dop2_PreEncode'),
    ('color', '0x10beaef0', 'ColorStackElements'),
]
PHASE_BY_NAME = {p[0]: p for p in PHASES}
INITIAL = '0x10c06890'
FUNCTION_GLOBAL = '0x10d0d700'          # c2!_Function

OPCODE_NAME = 0x10cdf220               # c2!_Opcode_name   char*[0x274], x86 opcodes
OPCODE_OPRNUM = 0x10cdfbf0             # c2!_Opcode_oprnum char[0x274]
OPCODE_DOPE = 0x10ce1e60               # c2!_Opcode_dope   dword[0x274]; bit 0x800: print src before dst
IL_NAME = 0x10cebda8                   # char*[161]: OPILLEGAL .. OP_LIMIT_, opcode - 0x274
IL_BASE = 0x274
REG_NAME = 0x10cec7b8                  # c2!_RegName       char*[], 1-based: eax ecx edx ebx esp ebp esi edi
COND_NAME = 0x10ce2b68                 # c2!_CondCodeName  char*[16], x86 encoding order
# c2!_TupCCEncode (0x10cec6e0): internal condition number -> x86 condition code. The tuple
# carries the internal number until EncCondCodes rewrites it, which is after every phase here.
CC_INTERNAL = {1: 'e', 2: 'ne', 3: 'l', 4: 'g', 5: 'le', 6: 'ge', 7: 'b', 8: 'a', 9: 'be',
               10: 'ae', 11: 's', 12: 'ns', 13: 'p', 14: 'np'}

# the IL opcode names, in table order (verified against the pointer table at IL_NAME:
# entry 49 is OPADD, entry 90 OPASM, entry 128 OPENTRY, entry 160 OP_LIMIT_)
IL_NAMES = ('OPILLEGAL OPICONST OPSCONST OPFCONST OPTEXT OPREG OPLOCAL OPGLOBAL OPBASED OPINDEXED '
            'OPLOCALSCALED OPSCALED OPSYMOFF OPSYMSEG OPSEGOFF OPEXTERNAL OPINTERNAL OPLABOFF OPPCREL '
            'OPFRAMESIZE OPREGSET OPSYMSET OPARG OPOUTARG OPMGDCONVERT OPASSIGN OPVOLATILEASSIGN OPLOAD '
            'OPSTORE OPCONVERT OPNOT OPNEG OPPAREN OPENTERLOAD OPEXITSAVE OPHASH OPHARDINTRIN OPOVCHECK '
            'OPOVCONVERT OPLEA OPLEA_LAB OPMBARG OPMBASSIGN OPMBOUTARG OPMBVOLATILEASSIGN OPRET OPPHI '
            'OPRHO OPINLINEARGS OPADD OPSUB OPMUL OPMULHI OPSHL OPAND OPOR OPXOR OPDIV OPREM OPDIVREM '
            'OPSHR OPRNGCHECK OPIVADD OPIVSUB OPIVMUL OPIVCONVERT OPCMP OPEQ OPNE OPLT OPGT OPLE OPGE '
            'OPSPADJUST OPCALL OPBRANCH OPGOTO OPCATCHRET OPFINALLYCALL OPFINALLYRET OPSCOPEGOTO '
            'OPSCOPEEXITGOTO OPONERROR OPEXITGOTO OPLEAVE OPSWITCH OPSCOPEEXIT OPQUESTION OPINTRINSIC '
            'OPTUPLIST OPASM OPTRY OPTRYEND OPFINALLY OPFINALLYEND OPEXCEPT OPEXCEPTEND OPFILTERSTART '
            'OPFILTER OPFILTEREND OPKILLREGS OPSIDEEFFECT OPSCOPEINDEX OPPUSHSTATE OPPOPSTATE '
            'OPDTORACTION OPDTOREND OPEHTRY OPCATCH OPEHENDTRY OPEHRET OPNEWSTATE OPSETSTATE OPARGPLACE '
            'OPCORTHROW OPCORRETHROW OPEHFINALLY OPEHFINALLYEND OPCOMOBJECT OPEHENDCATCH OPFAULT '
            'OPEHFAULT OPEHFAULTEND OPASSUME OPASSUMEEXPR OPPROBE OPLABEL OPBLOCK OPENTRY OPEXIT '
            'OPSPLITPOINT OPPROLOGEND OPEHPROLOGSTART OPEPILOGSTART OPBLKSTART OPBLKEND OPINLINE '
            'OPINTERLOCK OPALIGNCODE OPEMPTYBLOCK OPUSERLABEL OPSEGMENT OPSTATEMENT OPUSERSTATEMENT '
            'OPDEADCATCHRET OPINLINESTART OPINLINEEND OPPOGOPROLOGEND OPREGION OPEXCEPTCODEWARNOFFSTART '
            'OPEXCEPTCODEWARNOFFEND OPOMP_SECSTART OPOMP_SINGLE OPOMP_BARRIER OPOMP_MASTER OPOMP_ORDERED '
            'OPOMP_LASTPRIVATE OPOMP_COPYIN OPMSIL_DANGLINGCODE_START OPMSIL_DANGLINGCODE_END OP_LIMIT_').split()
IL = {IL_BASE + i: n for i, n in enumerate(IL_NAMES)}

# leaf (operand) opcodes
O_ICONST, O_SCONST, O_FCONST, O_TEXT, O_REG, O_LOCAL, O_GLOBAL, O_BASED, O_INDEXED = range(0x275, 0x27e)
O_LOCALSCALED, O_SCALED, O_SYMOFF, O_SYMSEG, O_SEGOFF, O_EXTERNAL, O_INTERNAL, O_LABOFF, O_PCREL = range(0x27e, 0x287)
O_REGSET, O_SYMSET = 0x288, 0x289
PSEUDO = {0x2f2: '.label', 0x2f3: '.block', 0x2f4: '.entry', 0x2f5: '.exit', 0x2f7: '.prologend',
          0x2f8: '.ehprologstart', 0x2f9: '.epilogstart', 0x2fa: '.blkstart', 0x2fb: '.blkend',
          0x2d9: '.sideeffect', 0x2e2: '.pushstate', 0x2e3: '.popstate', 0x302: '.statement',
          0x2f6: '.splitpoint'}


# ----------------------------------------------------------------------------------------------
# the cdb side: one script file, run with $$>a< from each phase breakpoint, that walks the
# function's block list and prints every tuple and operand as raw fields

def dump_script():
    """Lines of a cdb script. ${$arg1} is the Function record; ${$arg2} the phase tag."""
    # operand fields: see msvc-backend.md "Tuples and operands". Dereferences are gated per
    # opcode so a constant is never followed as a pointer.
    # a symbol's name, the way LiPrintBeSym/SymName resolve it: follow the alias at sym+8,
    # a sym with no name record at +0 is a temporary ("tv<id>", id at +0x1c), a kind-1 sym
    # (byte at +4) is a physical register (number at +0x1c), otherwise the name record at +0
    # holds a pointer at +4 to one byte before the string.
    # a symbol's name, the way LiPrintBeSym/SymName resolve it: follow the alias at sym+8;
    # a kind-1 sym (byte at +4) is a physical register (number at +0x1c); a sym whose +0 is a
    # name record names itself through namerec+4 (one byte before the string); a sym with no
    # name record is a temporary "tv<id>" (id at +0x1c) - except an external/function symbol,
    # whose +4 is itself the name pointer. Both candidates are printed; parse() keeps the one
    # that reads as a name.
    name = ('.if (@$t2 != 0) { .if (poi(@$t2+8) != 0) { r $t2=poi(@$t2+8) }; '
            '.if ((poi(@$t2+4)&0xff) == 1) { .printf ' + Q + 'reg%d' + N + Q + ', poi(@$t2+0x1c) } '
            '.elsif ((poi(@$t2) > 0x10000) & (poi(@$t2) < 0x7fff0000)) { .if ((poi(poi(@$t2)+4) > 0x10000) & (poi(poi(@$t2)+4) < 0x7fff0000)) { da poi(poi(@$t2)+4)+1 L80 } .else { .printf ' + Q + 'tv%d' + N + Q + ', poi(@$t2+0x1c) } } '
            '.elsif ((poi(@$t2+4) > 0x10000) & (poi(@$t2+4) < 0x7fff0000)) { da poi(@$t2+4)+1 L80 } '
            '.else { .printf ' + Q + 'tv%d' + N + Q + ', poi(@$t2+0x1c) } }')
    opr = (
        '.printf ' + Q + 'OPR${$arg3} %x %x b8=%x d10=%x b14=%x d18=%x d1c=%x d24=%x d28=%x d2c=%x d30=%x' + N + Q +
        ', @$t8, poi(@$t8+4), (poi(@$t8+8)&0xff), poi(@$t8+0x10), (poi(@$t8+0x14)&0xff), poi(@$t8+0x18), '
        'poi(@$t8+0x1c), poi(@$t8+0x24), poi(@$t8+0x28), poi(@$t8+0x2c), poi(@$t8+0x30); '
        'r $t7=poi(@$t8+4); '
        # register number of a register operand: [[op+0x1c]+0x1c]
        '.if (@$t7 == 0x279) { r $t2=poi(@$t8+0x1c); .printf ' + Q + 'REG %x ' + Q + ', @$t8; ' + name + ' }; '
        # an external/internal (function) symbol at +0x18 names itself through +4 directly, no alias
        '.if ((@$t7 == 0x283) | (@$t7 == 0x284)) { r $t2=poi(@$t8+0x18); .if (@$t2 != 0) { .if ((poi(@$t2+4) > 0x10000) & (poi(@$t2+4) < 0x7fff0000)) { .printf ' + Q + 'SYM %x ' + Q + ', @$t8; da poi(@$t2+4)+1 L80 } .else { .printf ' + Q + 'LAB %x %x' + N + Q + ', @$t8, @$t2 } } }; '
        # symbol at +0x18: SCONST LOCAL GLOBAL
        '.if ((@$t7 == 0x276) | (@$t7 == 0x27a) | (@$t7 == 0x27b)) { '
        'r $t2=poi(@$t8+0x18); .printf ' + Q + 'SYM %x ' + Q + ', @$t8; ' + name + '; '
        '.if (@$t2 != 0) { .printf ' + Q + 'SOFF %x %x %x' + N + Q + ', @$t8, poi(@$t2+0x24), poi(@$t2+8) } }; '
        # symbol at +0x24: BASED INDEXED LOCALSCALED SCALED SYMOFF SYMSEG SEGOFF
        '.if ((@$t7 >= 0x27c) & (@$t7 <= 0x282)) { r $t2=poi(@$t8+0x24); .if (@$t2 != 0) { .printf ' + Q + 'SYM %x ' + Q + ', @$t8; ' + name + '; '
        '.printf ' + Q + 'SOFF %x %x %x' + N + Q + ', @$t8, poi(@$t2+0x24), poi(@$t2+8) } }; '
        # base / index operands of a memory form: each is a leaf whose [[+0x1c]+0x1c] is the register
        '.if ((@$t7 == 0x27c) | (@$t7 == 0x27d)) { .if (poi(@$t8+0x2c) != 0) { r $t2=poi(poi(@$t8+0x2c)+0x1c); .printf ' + Q + 'BASE %x ' + Q + ', @$t8; ' + name + ' } }; '
        '.if ((@$t7 >= 0x27d) & (@$t7 <= 0x27f)) { .if (poi(@$t8+0x30) != 0) { r $t2=poi(poi(@$t8+0x30)+0x1c); .printf ' + Q + 'INDEX %x ' + Q + ', @$t8; ' + name + ' } }'
    )
    lines = [
        '.printf ' + Q + 'PHASE ${$arg2} fn=%x' + N + Q + ', ${$arg1}',
        'r $t3=poi(poi(${$arg1}+8)); r $t4=0',
        '.while ((@$t3 != 0) & (@$t4 < 0n400)) {',
        '  .printf ' + Q + 'BLK %d %x num=%d' + N + Q + ', @$t4, @$t3, poi(@$t3+0x178);',
        '  r $t5=poi(@$t3+8); .while (@$t5 != 0) { .printf ' + Q + 'PRED %x' + N + Q + ', poi(@$t5+8); r $t5=poi(@$t5+4) };',
        '  r $t5=poi(@$t3+0xc); .while (@$t5 != 0) { .printf ' + Q + 'SUCC %x' + N + Q + ', poi(@$t5+0xc); r $t5=poi(@$t5) };',
        '  r $t5=poi(poi(@$t3+0x1c)); r $t6=0;',
        '  .while ((@$t5 != 0) & (@$t6 < 0n2000) & (@$t5 != poi(@$t3+0x20))) {',
        '    .printf ' + Q + 'TUP %x op=%x k=%x f=%x w=%x d1c=%x d20=%x d24=%x d28=%x d2c=%x d30=%x' + N + Q +
        ', @$t5, poi(@$t5+4), (poi(@$t5+8)&0xff), (poi(@$t5+9)&0xff), (poi(@$t5+0xa)&0xffff), poi(@$t5+0x1c), poi(@$t5+0x20), poi(@$t5+0x24), poi(@$t5+0x28), poi(@$t5+0x2c), poi(@$t5+0x30);',
        # operand lists only for real instructions (flags bit 0, as LiPrintBlock counts them):
        # a pseudo tuple's +0x28/+0x2c hold other things, and following them aborts the script
        '    .if ((poi(@$t5+9)&1) != 0) {',
        '    r $t8=poi(@$t5+0x28); r $t1=0; .while ((@$t8 != 0) & (@$t1 < 0n16)) { r $t1=@$t1+1; ' + opr.replace('${$arg3}', 'D') + '; r $t8=poi(@$t8) };',
        '    r $t8=poi(@$t5+0x2c); r $t1=0; .while ((@$t8 != 0) & (@$t1 < 0n16)) { r $t1=@$t1+1; ' + opr.replace('${$arg3}', 'S') + '; r $t8=poi(@$t8) } };',
        '    r $t5=poi(@$t5); r $t6=@$t6+1 };',
        '  r $t3=poi(@$t3); r $t4=@$t4+1 }',
        '.printf ' + Q + 'ENDPHASE' + N + Q,
    ]
    return lines


def tables_script():
    lines = ['.for (r $t1=0; @$t1 < 0x274; r $t1=@$t1+1) { .printf ' + Q + 'XOP %d %d ' + Q +
             ', @$t1, (poi(0x%x+@$t1)&0xff); da poi(0x%x+@$t1*4) L20 }' % (OPCODE_OPRNUM, OPCODE_NAME),
             '.for (r $t1=0; @$t1 < 0x274; r $t1=@$t1+1) { .printf ' + Q + 'DOPE %d %x' + N + Q + ', @$t1, poi(0x%x+@$t1*4) }' % OPCODE_DOPE,
             '.for (r $t1=0; @$t1 < 0n161; r $t1=@$t1+1) { .printf ' + Q + 'ILOP %d ' + Q + ', @$t1; da poi(0x%x+@$t1*4) L40 }' % IL_NAME,
             '.for (r $t1=0; @$t1 < 0n40; r $t1=@$t1+1) { .printf ' + Q + 'REG %d ' + Q + ', @$t1; da poi(0x%x+@$t1*4) L8 }' % REG_NAME,
             '.for (r $t1=0; @$t1 < 0n16; r $t1=@$t1+1) { .printf ' + Q + 'CC %d ' + Q + ', @$t1; da poi(0x%x+@$t1*4) L8 }' % COND_NAME]
    return lines


def refresh_tables(src):
    """One compile under cdb that reads c2's name tables and writes c2_tables.json."""
    path = out / 'tables.cdb'
    slot_probe.common.write_text(path, c2base.rebase('\r\n'.join(['sxe ld:c2', 'g'] + tables_script() + ['q', ''])))
    cmd, cwd = slot_probe.compile_command(src, 'tables')
    import subprocess
    env = slot_probe.common.build_env()
    env['PATH'] = str(slot_probe.common.ROOT / 'MSVC1400-SP1' / 'Common7' / 'IDE') + os.pathsep + env['PATH']
    r = subprocess.run('"%s" -cf "%s" %s' % (slot_probe.CDB, path, cmd), cwd=cwd, env=env,
                       capture_output=True, text=True, timeout=3600)
    txt = r.stdout
    slot_probe.common.write_text(out / 'tables.log', txt)
    t = {'x86': {}, 'oprnum': {}, 'dope': {}, 'il': {}, 'reg': {}, 'cc': {}}
    for m in re.finditer(r'^XOP (\d+) (\d+) [0-9a-f]+\s+"([^"]*)"', txt, re.M):
        t['x86'][m.group(1)] = m.group(3)
        t['oprnum'][m.group(1)] = int(m.group(2))
    for m in re.finditer(r'^DOPE (\d+) ([0-9a-f]+)', txt, re.M):
        t['dope'][m.group(1)] = int(m.group(2), 16)
    for m in re.finditer(r'^ILOP (\d+) [0-9a-f]+\s+"([^"]*)"', txt, re.M):
        t['il'][m.group(1)] = m.group(2)
    for m in re.finditer(r'^REG (\d+) [0-9a-f]+\s+"([^"]*)"', txt, re.M):
        t['reg'][m.group(1)] = m.group(2)
    for m in re.finditer(r'^CC (\d+) [0-9a-f]+\s+"([^"]*)"', txt, re.M):
        t['cc'][m.group(1)] = m.group(2)
    if len(t['x86']) < 0x270 or len(t['il']) < 160:
        sys.exit('could not read the tables - see ' + str(out / 'tables.log'))
    with open(TABLES, 'w', encoding='utf-8') as f:
        json.dump(t, f, indent=0, sort_keys=True)
    print('wrote %s: %d x86 opcodes, %d IL opcodes, %d registers' % (TABLES, len(t['x86']), len(t['il']), len(t['reg'])))


def load_tables():
    if not os.path.exists(TABLES):
        sys.exit('no %s - run tuple_dump.py --tables FILE.cpp once' % TABLES)
    with open(TABLES, encoding='utf-8') as f:
        t = json.load(f)
    return ({int(k): v for k, v in t['x86'].items()}, {int(k): v for k, v in t['il'].items()},
            {int(k): v for k, v in t['reg'].items()}, {int(k): v for k, v in t['cc'].items()},
            {int(k): v for k, v in t['oprnum'].items()}, {int(k): v for k, v in t['dope'].items()})


# ----------------------------------------------------------------------------------------------
# running it

def probe(src, name, phases):
    script = out / 'tupdump.cdb'
    slot_probe.common.write_text(script, c2base.rebase('\r\n'.join(dump_script()) + '\r\n'))
    n = len(phases)
    # the gate: at the first phase of every function, compare the mangled name (poi(poi(eax)+4)
    # is "?name@Class@...") and arm or disarm the phase breakpoints. $t9 remembers the Function.
    gate = ('r $t7=poi(poi(@eax)+4); ' + slot_probe.name_test(name) + '; .if (@$t6 != 0) { r $t9=@eax; .printf '
            + EQ + 'FOUND' + NL + EQ + '; be 1-%d } .else { r $t9=0; bd 1-%d }' % (n, n))
    lines = ['sxe ld:c2', 'g']
    sp = str(script).replace('\\', '\\\\')
    for i, (tag, addr, _sym) in enumerate(phases):
        if addr == INITIAL:
            # same address as the gate: dump from inside the gate instead
            continue
        lines.append('bp%d %s "$$>a<%s @$t9 %s; gc"' % (i + 1, addr, sp, tag))
    lines.append('bd 1-%d' % n)
    want_initial = any(a == INITIAL for _t, a, _s in phases)
    lines.append('bp0 ' + INITIAL + ' "' + gate + ('; .if (@$t9 != 0) { $$>a<%s @$t9 initial }' % sp if want_initial else '') + '; gc"')
    lines += ['g', 'q', '']
    txt = run(lines, src, 'tuples-%s-%s' % (os.path.basename(src)[:-4], name))
    if 'Malformed' in txt or 'Syntax error' in txt:
        sys.exit('cdb rejected a command - see ' + str(out))
    if 'FOUND' not in txt:
        sys.exit('function %s not seen at dop2_InitialOptsAndSetup - check the name (the mangled name must start with ?NAME@)' % name)
    return txt


# ----------------------------------------------------------------------------------------------
# decoding

class Opr(object):
    __slots__ = ('addr', 'op', 'b8', 'd10', 'b14', 'd18', 'd1c', 'd24', 'd28', 'd2c', 'd30',
                 'reg', 'sym', 'soff', 'sbase', 'base', 'index')

    def __init__(self):
        self.reg = self.base = self.index = None
        self.sym = None
        self.soff = self.sbase = 0


def parse(txt):
    """{phase: [block]} where block = (idx, addr, num, preds, succs, [tuple]) and
    tuple = (addr, op, kind, flags, w, d1c, d20, [Opr dst], [Opr src])."""
    phases = {}
    cur = None
    blk = None
    tup = None
    oprs = {}
    for line in txt.splitlines():
        line = line.strip()
        if line.startswith('PHASE '):
            tag = line.split()[1]
            cur = phases.setdefault(tag, [])
            continue
        if cur is None:
            continue
        if line.startswith('BLK '):
            m = re.match(r'BLK (\d+) ([0-9a-f]+) num=(-?\d+)', line)
            blk = [int(m.group(1)), int(m.group(2), 16), int(m.group(3)), [], [], []]
            cur.append(blk)
        elif line.startswith('PRED '):
            blk[3].append(int(line.split()[1], 16))
        elif line.startswith('SUCC '):
            blk[4].append(int(line.split()[1], 16))
        elif line.startswith('TUP '):
            m = re.match(r'TUP ([0-9a-f]+) op=([0-9a-f]+) k=([0-9a-f]+) f=([0-9a-f]+) w=([0-9a-f]+) d1c=([0-9a-f]+) d20=([0-9a-f]+) d24=([0-9a-f]+)', line)
            if not m:
                continue
            tup = [int(m.group(i), 16) for i in range(1, 8)] + [[], [], int(m.group(8), 16)]
            blk[5].append(tup)
        elif line.startswith('OPR'):
            m = re.match(r'OPR([DS]) ([0-9a-f]+) ([0-9a-f]+) b8=([0-9a-f]+) d10=([0-9a-f]+) b14=([0-9a-f]+) d18=([0-9a-f]+) d1c=([0-9a-f]+) d24=([0-9a-f]+) d28=([0-9a-f]+) d2c=([0-9a-f]+) d30=([0-9a-f]+)', line)
            if not m or tup is None:
                continue
            o = Opr()
            o.addr, o.op, o.b8, o.d10, o.b14, o.d18, o.d1c, o.d24, o.d28, o.d2c, o.d30 = [int(m.group(i), 16) for i in range(2, 13)]
            tup[7 if m.group(1) == 'D' else 8].append(o)
            oprs[o.addr] = o
        elif line.startswith('LAB '):
            a, symaddr = line.split()[1:3]
            if int(a, 16) in oprs:
                oprs[int(a, 16)].sym = 'label:' + symaddr
        elif line.startswith(('REG ', 'BASE ', 'INDEX ', 'SYM ')):
            m = re.match(r'(REG|BASE|INDEX|SYM) ([0-9a-f]+) (?:[0-9a-f]{8}\s+"([^"]*)"|(reg\d+|tv\d+))', line)
            if not m or int(m.group(2), 16) not in oprs:
                continue
            val = m.group(3) if m.group(3) is not None else m.group(4)
            o = oprs[int(m.group(2), 16)]
            if m.group(1) == 'SYM':
                o.sym = val
            else:
                setattr(o, {'REG': 'reg', 'BASE': 'base', 'INDEX': 'index'}[m.group(1)], val)
        elif line.startswith('SOFF '):
            a, off, base = line.split()[1:4]
            if int(a, 16) in oprs:
                oprs[int(a, 16)].soff = int(off, 16)
                oprs[int(a, 16)].sbase = int(base, 16)
    return phases


def s32(v):
    return v - (1 << 32) if v & 0x80000000 else v


class Renderer(object):
    def __init__(self):
        self.x86, self.il, self.reg, self.cc, self.oprnum, self.dope = load_tables()
        self.labels = {}

    SUB = {1: {1: 'al', 2: 'cl', 3: 'dl', 4: 'bl'}, 2: {1: 'ax', 2: 'cx', 3: 'dx', 4: 'bx', 5: 'sp', 6: 'bp', 7: 'si', 8: 'di'}}

    def regname(self, n, size=4):
        """n is what the name macro printed for the register symbol: reg<k> for a physical
        register (c2's 1-based numbering), tv<k> for a pseudo-register, a name for a candidate."""
        if n is None:
            return 'r?'
        if n.startswith('reg') and n[3:].isdigit():
            k = int(n[3:])
            if size in self.SUB and k in self.SUB[size]:
                return self.SUB[size][k]
            return self.reg.get(k, 'r%s' % k)
        if n.startswith('tv'):
            return 't' + n[2:]
        return n

    def opname(self, op, w):
        if op < IL_BASE:
            n = self.x86.get(op, 'x86_%x' % op)
            if op == 0xf:                                   # _jcc: j + condition
                n = 'j' + CC_INTERNAL.get(w & 0xf, '?%d' % (w & 0xf))
            return n
        return self.il.get(op - IL_BASE, IL.get(op, 'op_%x' % op))

    def size_prefix(self, w):
        return {1: 'byte ptr ', 2: 'word ptr ', 4: 'dword ptr ', 8: 'qword ptr '}.get(w & 0xfff, '')

    def operand(self, o, w):
        op = o.op
        if op == O_ICONST:
            return str(s32(o.d18))
        if op == O_SCONST:
            return '%s(=%d)' % (o.sym or '?', s32(o.soff))
        if op == O_REG:
            if o.reg is None:
                return 't@%x' % o.d1c
            return self.regname(o.reg, w & 0xfff)
        if op == O_LOCAL:
            name = o.sym or '(temp)'
            return '%s%s' % (self.size_prefix(w), name)
        if op == O_GLOBAL:
            name = o.sym or '?'
            off = s32(o.soff)
            if o.b8 == 2:
                return '%s[%s%s]' % (self.size_prefix(w), name, ('%+d' % off) if off else '')
            return 'OFFSET %s%s' % (name, ('%+d' % off) if off else '')
        if op in (O_BASED, O_INDEXED, O_LOCALSCALED, O_SCALED):
            parts = []
            if op in (O_BASED, O_INDEXED):
                parts.append(self.regname(o.base))
            if op == O_LOCALSCALED:
                parts.append('frame')
            if op in (O_INDEXED, O_LOCALSCALED, O_SCALED):
                idx = self.regname(o.index)
                sc = 1 << (o.b14 & 0xf)
                parts.append(idx + ('*%d' % sc if sc > 1 else ''))
            off = s32(o.d28) - (s32(o.d10) if op in (O_INDEXED, O_LOCALSCALED) else 0)
            inner = ' + '.join(p for p in parts if p)
            if off:
                inner += ' %s %d' % ('+' if off > 0 else '-', abs(off))
            return '%s%s[%s]' % (self.size_prefix(w), (o.sym or ''), inner)
        if op == O_SYMOFF:
            return 'OFFSET %s%s' % (o.sym or '?', ('%+d' % s32(o.d28)) if o.d28 else '')
        if op == O_SYMSEG:
            return 'SEG %s' % (o.sym or '?')
        if op == O_SEGOFF:
            return 'seg:%s' % (o.sym or '?')
        if op in (O_EXTERNAL, O_INTERNAL):
            if o.sym and o.sym.startswith('label:'):
                return self.label(int(o.sym[6:], 16))
            return o.sym or '?'
        if op == O_LABOFF:
            return self.label(o.d28)
        if op == O_PCREL:
            return '$%+d' % s32(o.d28)
        if op == O_REGSET:
            return 'regset'
        if op == O_SYMSET:
            return 'symset'
        return '%s@%x' % (self.il.get(op - IL_BASE, 'op%x' % op) if op >= IL_BASE else 'op%x' % op, o.addr)

    def label(self, addr):
        if addr not in self.labels:
            self.labels[addr] = 'L%d' % (len(self.labels) + 1)
        return self.labels[addr]

    def render(self, blocks, raw=False):
        lines = []
        for idx, addr, num, preds, succs, tuples in blocks:
            # label every tuple that is a branch target so jumps read as `jne L3`
            for t in tuples:
                if t[1] == 0x2f2:
                    self.label(t[9])          # the label's symbol, which branch operands name
            pr = ','.join(str(self.blocknum(blocks, p)) for p in preds)
            su = ','.join(str(self.blocknum(blocks, s)) for s in succs)
            lines.append('BLK %d  preds=%s  succs=%s' % (num, pr or '-', su or '-'))
            for t in tuples:
                taddr, op, kind, flags, w, d1c, d20, dst, src, d24 = t
                if op in PSEUDO or (op >= IL_BASE and kind in (0x17, 0x18, 0x19, 0x1a, 0x1b)):
                    nm = PSEUDO.get(op, self.opname(op, w).lower())
                    if op == 0x2f2:
                        lines.append('  %s:' % self.label(d24))
                    else:
                        lines.append('      %-14s' % nm + (' ; kind=%x' % kind if raw else ''))
                    continue
                name = self.opname(op, w)
                ops = [self.operand(o, w) for o in self.listed(op, dst, src)]
                if op >= IL_BASE and dst:
                    text = '%s = %s(%s)' % (', '.join(self.operand(o, w) for o in dst), name,
                                            ', '.join(self.operand(o, w) for o in src))
                elif op >= IL_BASE:
                    text = '%s(%s)' % (name, ', '.join(self.operand(o, w) for o in src))
                else:
                    text = '%-9s %s' % (name, ', '.join(ops))
                extra = ''
                if raw:
                    extra = '   ; %x k=%x f=%x w=%x' % (taddr, kind, flags, w)
                lines.append('      ' + text + extra)
        return lines

    def listed(self, op, dst, src):
        """The operands the listing writer prints for an x86 tuple (MdPrintInstr): `oprnum`
        of them, starting with the src list when dope bit 0x800 is set, else dst then src.
        The rest are implicit (esp for push/pop, the clobber sets of a call)."""
        if op >= IL_BASE:
            return dst + src
        n = self.oprnum.get(op, 0)
        if n <= 0:
            return []
        first_src = bool(self.dope.get(op, 0) & 0x800)
        seq = (src + dst) if first_src else (dst + src)
        return seq[:n]

    def blocknum(self, blocks, addr):
        for idx, a, num, _p, _s, _t in blocks:
            if a == addr:
                return num
        return -1


def main():
    argv = sys.argv[1:]
    if '--tables' in argv:
        src = next((a for a in argv if a.endswith('.cpp')), None)
        if not src:
            # any file in the build list will do - the tables are static data in c2.dll
            files = slot_probe.common.list_files()
            if not files:
                sys.exit('give a .cpp to compile')
            src = str(files[0])
        refresh_tables(os.path.abspath(src))
        return
    src = next((a for a in argv if a.endswith('.cpp')), None)
    name = argv[argv.index('--name') + 1] if '--name' in argv else None
    if not src or not name:
        sys.exit(__doc__)
    raw = '--raw' in argv
    if '--diff' in argv:
        i = argv.index('--diff')
        want = [argv[i + 1], argv[i + 2]]
    elif '--at' in argv:
        want = argv[argv.index('--at') + 1].split(',')
    else:
        want = [p[0] for p in PHASES]
    bad = [w for w in want if w not in PHASE_BY_NAME]
    if bad:
        sys.exit('unknown phase(s) %s; known: %s' % (bad, ' '.join(p[0] for p in PHASES)))
    phases = [PHASE_BY_NAME[w] for w in want]
    txt = probe(os.path.abspath(src), name, phases)
    data = parse(txt)
    r = Renderer()
    rendered = {}
    for tag, _a, sym in phases:
        if tag not in data:
            print('### %s (%s): no dump - the phase did not run for this function' % (tag, sym))
            continue
        rendered[tag] = r.render(data[tag], raw)
    if '--diff' in argv:
        import difflib
        a, b = want
        for l in difflib.unified_diff(rendered.get(a, []), rendered.get(b, []), a, b, lineterm='', n=3):
            print(l)
        return
    for tag, _a, sym in phases:
        if tag in rendered:
            n = sum(1 for l in rendered[tag] if not l.startswith('BLK') and not l.strip().startswith('.') and not l.strip().endswith(':'))
            print('### %s  (%s)  %d instruction tuples' % (tag, sym, n))
            for l in rendered[tag]:
                print(l)
            print('')


if __name__ == '__main__':
    main()
