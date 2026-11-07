"""Make cdb scripts independent of where c2.dll is mapped.

The probes hard-code c2.dll addresses from its preferred base (0x10b00000, the PDB's). A large
translation unit can leave that range taken by the time c2.dll loads, so the loader rebases it and
every `bp 0x10c07350` fails with Win32 error 299. `rebase()` rewrites each address inside c2's
image as `(@$t19+offset)` and, right after the `sxe ld:c2` / `g` pair that every probe starts
with, loads `$t19` with the module's actual base. Scripts run with `$$>a<` from such a script see
the same `$t19`. (`c2+offset` does not work: MASM evaluation reads `c2` as the number 0xc2;
`@!"c2"` forces the module name, but cannot sit inside a quoted breakpoint command.)
"""

import re

C2_BASE = 0x10b00000
C2_END = 0x10d5f000
LOAD_BREAK = re.compile(r'(sxe ld:c2\r?\ng\r?\n)')


def _sub(m):
    v = int(m.group(0), 16)
    if C2_BASE <= v < C2_END:
        return '(@$t19+0x%x)' % (v - C2_BASE)
    return m.group(0)


def rebase(text):
    # A rebased c2.dll raises the load event twice at the same base (mapped, then mapped again for
    # the relocation); breakpoints set at the first are lost, so go on to the second one.
    text = re.sub(r'0x10[b-dB-D][0-9a-fA-F]{5}\b', _sub, text)
    nl = '\r\n' if '\r\n' in text else '\n'
    after = '.if (@!"c2" != 0x10b00000) { g }' + nl + 'r $t19=@!"c2"' + nl
    return LOAD_BREAK.sub(lambda m: m.group(1) + after, text, 1)
