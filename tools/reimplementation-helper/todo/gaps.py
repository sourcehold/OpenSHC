import os, re

# data files are read from and written to the current working directory (run from the repo root)
SCRATCH = os.getcwd()
expected = set(open(os.path.join(SCRATCH, 'expected_cpp.txt'), encoding='utf-8').read().split())
lower = {p.lower(): p for p in expected}

extras = [
    'src/OpenSHC/IO/LowLevelMemory/fillMemory.cpp',
    'src/OpenSHC/IO/ResourceManager/mapNames.cpp',
    'src/OpenSHC/IO/ResourceManager/paths.cpp',
    'src/OpenSHC/IO/readSkMasters2.cpp',
    'src/OpenSHC/Map/Units/UnitsState/ComputeDamageFearFactorBonus.cpp',
    'src/OpenSHC/OS/OS.cpp',
    'src/OpenSHC/Text/TextEditorState/helpToken.cpp',
    'src/OpenSHC/UI/Rendering/TextureRenderCore/CheckGfxResourceExists.cpp',
]
print('== extras, case-insensitive hit in expected? ==')
for e in extras:
    print(' ', e, '->', lower.get(e.lower(), 'NO MATCH'))

# hpp files with no sibling .func.hpp that still declare a non-inline function
print()
print('== .hpp without .func.hpp but with declarations that look like functions ==')
decl = re.compile(r'^\s{4,}(?!//)(?:virtual\s+|static\s+|inline\s+)?[A-Za-z_][\w:<>,\s\*&]*?\b([A-Za-z_]\w*)\s*\([^;{]*\)\s*(?:const\s*)?;\s*$')
hits = 0
for dirpath, dirs, files in os.walk('src/OpenSHC'):
    for fn in files:
        if not fn.endswith('.hpp') or fn.endswith('.func.hpp'):
            continue
        p = os.path.join(dirpath, fn).replace(os.sep, '/')
        if os.path.exists(p[:-4] + '.func.hpp'):
            continue
        cls = os.path.basename(p)[:-4]
        names = []
        for line in open(p, encoding='utf-8', errors='replace'):
            m = decl.match(line.rstrip('\n'))
            if not m:
                continue
            n = m.group(1)
            if n in (cls, '~' + cls) or n.startswith('operator') or 'static_assert' in line:
                continue
            if re.match(r'^\s*(class|struct|enum|typedef|using|friend|return|MACRO)', line):
                continue
            names.append(n)
        if names:
            hits += 1
            print(' ', p, sorted(set(names)))
print('files:', hits)
