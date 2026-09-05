"""Compare a VS2005 /O2 DLL-mode object with original SHC 1.41 under x86 emulation.

Requires pefile, capstone and unicorn. No game process or copyrighted binary is included.
"""
from pathlib import Path
import argparse, struct, random, hashlib
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import *

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('object',type=Path)
parser.add_argument('original',type=Path)
args=parser.parse_args()
obj=args.object.read_bytes()
_,nsec,_,symptr,nsyms,optsize,_=struct.unpack_from('<HHIIIHH',obj)
strings=obj[symptr+nsyms*18:]
symbols={}
i=0
while i<nsyms:
    pos=symptr+i*18
    raw,value,section,typ,storage,naux=struct.unpack_from('<8sIhHBB',obj,pos)
    name=(strings[struct.unpack_from('<I',raw,4)[0]:].split(b'\0')[0] if raw[:4]==b'\0'*4 else raw.split(b'\0')[0]).decode()
    symbols[i]=(name,value,section)
    i+=1+naux
name,start,section=next(v for v in symbols.values() if v[0].startswith('?clearStockpileFootprintTiles@'))
sec=20+optsize+(section-1)*40
size,rawptr,relptr=struct.unpack_from('<III',obj,sec+16)
nrel=struct.unpack_from('<H',obj,sec+32)[0]
code=bytearray(obj[rawptr:rawptr+size])
for i in range(nrel):
    offset,sym,kind=struct.unpack_from('<IIH',obj,relptr+i*10)
    symbol=symbols[sym][0]
    assert kind==6, (symbol,kind)
    addr=next(a for n,a in [('TerrainDefinedData',0xb48f54),('ViewportRenderState',0x21aebd8),('BuildingsState',0xf98520)] if n in symbol)
    struct.pack_into('<I',code,offset,struct.unpack_from('<I',code,offset)[0]+addr)
assert hashlib.sha256(args.original.read_bytes()).hexdigest()=='3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a', 'Unsupported original executable'
original=pefile.PE(str(args.original))
native=original.get_data(0x4faf70-0x400000,0x150)
for insn in Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,0x4faf70):
    if insn.mnemonic=='ret':
        native=native[:insn.address+insn.size-0x4faf70]
        break
else:
    raise AssertionError('Original return not found')
print('Recompiled code bytes:',len(code),'relocations:',nrel)
print('Original/recompiled byte equality:',bytes(code)==native)
assert bytes(code)==native, 'Machine code differs after resolving global relocations'
REGS=[UC_X86_REG_EBX,UC_X86_REG_EBP,UC_X86_REG_ESI,UC_X86_REG_EDI]
rng=random.Random(30)
def execute(payload, data, x, y, this):
    uc=Uc(UC_ARCH_X86,UC_MODE_32)
    uc.mem_map(0x400000,0x3000000)
    uc.mem_write(0x600000,bytes(payload))
    uc.mem_write(this,bytes(data))
    uc.mem_write(0xb49130,original.get_data(0xb49130-0x400000,72))
    for row in range(400): uc.mem_write(0x2337300+row*12,struct.pack('<I',row*200))
    for bid in range(32): uc.mem_write(0xf985f8+bid*0x32c,struct.pack('<H',bid%3))
    stack=0x3300000
    uc.mem_write(stack,struct.pack('<III',0x610000,x,y))
    uc.reg_write(UC_X86_REG_ESP,stack)
    uc.reg_write(UC_X86_REG_ECX,this)
    for i,reg in enumerate(REGS):uc.reg_write(reg,0x12345000+i)
    uc.emu_start(0x600000,0x610000,count=10000)
    assert uc.reg_read(UC_X86_REG_EIP)==0x610000
    assert uc.reg_read(UC_X86_REG_ESP)==stack+12
    assert [uc.reg_read(r) for r in REGS]==[0x12345000+i for i in range(4)]
    return bytes(uc.mem_read(this,len(data)))
offsets=struct.unpack('<18i',original.get_data(0xb49130-0x400000,72))
for case in range(32):
    this=0x1a93208 if case%2==0 else 0x2600000
    x,y=rng.randrange(10,180),rng.randrange(10,380)
    data=bytearray(rng.randbytes(0x554a88))
    for i in range(9):
        tile=(y+offsets[i*2+1])*200+x+offsets[i*2]
        struct.pack_into('<H',data,0x798a0+tile*2,(case+i)%32)
    a=execute(native,data,x,y,this)
    b=execute(code,data,x,y,this)
    assert a==b,case
print('PASS: 32 randomized full TileMapState differential comparisons, both noRubble branches, zero and nonzero building IDs, original and relocated this; stack and callee-saved registers preserved.')
