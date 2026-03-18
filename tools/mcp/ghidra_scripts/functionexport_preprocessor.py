#TODO write a description for this script
#@author 
#@category _OPENSHC.TOOLS
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


#TODO Add User Code Here

# preprocess_thiscall_dat.py
#
# Ghidra Python script to preprocess decompiled __thiscall functions,
# replacing DAT_<StructName>.<field> with this-><field>.
#
# The rule: Ghidra emits DAT_FooObject.field for __thiscall methods because
# it sees the global-like address that ECX points to. In the reimplementation,
# these become this->field since ECX *is* the this pointer.
#
# Usage:
#   Run from Ghidra Script Manager, or via analyzeHeadless:
#     analyzeHeadless <project> <program> -postScript preprocess_thiscall_dat.py
#
# Output:
#   Prints preprocessed source to the Ghidra console, and optionally writes
#   it to a file (set OUTPUT_DIR below).
#


import re
import os

from ghidra.app.decompiler import ClangReturnType, ClangVariableDecl, DecompileResults
from ghidra.program.model.pcode import PcodeBlockBasic
from ghidra.program.model.pcode import PcodeOpAST
from ghidra.program.model.pcode import HighGlobal
from ghidra.program.model.pcode import HighConstant
from ghidra.program.database.data import EnumDB
from ghidra.app.decompiler import ClangFunction
from ghidra.app.decompiler import ClangStatement
from ghidra.app.decompiler import ClangFuncProto
from ghidra.app.decompiler import ClangFuncNameToken

# ----------------------------------------------------------------------------
# Configuration
# ----------------------------------------------------------------------------

# Set to a directory path to write output .cpp files, or None to print only.
OUTPUT_DIR = None  # e.g. "C:/Users/Gynt/Projects/sourcehold/openshc/src_preprocessed"

# If True, also replace DAT_<X>::ptr-> (cross-object struct globals) with
# the proper accessor pattern for reference in comments. Does NOT change
# cross-object references — those are __cdecl and must keep DAT_X::ptr->.
ANNOTATE_CDECL_GLOBALS = True


# ----------------------------------------------------------------------------
# Core transformation
# ----------------------------------------------------------------------------

import java.math.BigInteger

def get_thiscall_dat_prefix(func, toAddr):
    """
    Detect which DAT_<name> prefix is used for 'this' in the given source.

    Ghidra names the global after the struct type, e.g. DAT_TextManagerObject,
    DAT_TileMapStateObject, etc. We find all DAT_ tokens that are followed by
    a '.' (member access) — those are __thiscall this-references.

    Returns a list of (dat_prefix, struct_name) tuples found.
    """
    ECX = [r for r in func.getProgram().getLanguage().getRegisters() if r.getName() == "ECX"][0]
    ECX_value = func.getProgram().getListing().getCodeUnitAt(func.getEntryPoint()).getRegisterValue(ECX)
    ECX_label = ""
    if ECX_value:
        ECX_value = ECX_value.getUnsignedValue()
        if isinstance(ECX_value, java.math.BigInteger):
            ECX_value = int(ECX_value.toString(), 10)
        ECX_label = func.getProgram().getListing().getCodeUnitAt(toAddr(ECX_value)).getLabel()
        return ECX_label
    return None


def replace_this_references(source, dat_prefix):
    """
    Replace DAT_<name>.<field> with this-><field> for all detected this-prefixes.
    Handles:
      DAT_Foo.field          -> this->field
      DAT_Foo.field.subfield -> this->field.subfield  (chained)
      ADJ(ptr)->owner        -> *ptr  (Ghidra ADJ artefact, same address)
    """
    result = source
    
    if dat_prefix:
        # Replace DAT_FooObject.field with this->field
        # Use word boundary on the left, match the dot accessor
        pattern = re.compile(r'\b' + re.escape(dat_prefix) + r'\.(\w+)')
        result = pattern.sub(r'this->\1', result)
        pattern = re.compile(r'&' + re.escape(dat_prefix) + r'')
        result = pattern.sub('this', result)
    
    # Handle Ghidra's ADJ() artefact: ADJ(expr)->field means same address,
    # just different type view. In __thiscall context this is this->field
    # where expr is the same pointer. Replace ADJ(x)->field with x->field.
    result = re.sub(r'\bADJ\(([^)]+)\)->(\w+)', r'\1->\2', result)
    
    return result


def annotate_cdecl_globals(source):
    """
    Add a comment marker next to DAT_Foo::ptr references so the implementer
    knows these are cross-object globals requiring the ::ptr accessor pattern.
    Does not change the text — purely informational.
    """
    # Match DAT_Xxx::ptr (but not if already commented)
    pattern = re.compile(r'(DAT_\w+::ptr)')
    result = pattern.sub(r'\1 /* cross-object global, keep ::ptr */', source)
    return result


def strip_ghidra_signature_comments(source):
    """
    Remove the Ghidra-emitted block comment header (===... lines) if present,
    since the reimplementation will have its own header.
    """
    lines = source.splitlines()
    out = []
    in_header = False
    header_done = False
    for line in lines:
        if not header_done:
            stripped = line.strip()
            if stripped.startswith('// ====='):
                in_header = True
                continue
            if in_header:
                if stripped.startswith('//'):
                    continue  # still in header block
                else:
                    in_header = False
                    header_done = True
        out.append(line)
    return '\n'.join(out)


def fix_thiscall_param(source):
    """
    Remove the explicit 'this' parameter from the function signature.
    Ghidra emits:  void __thiscall Foo(FooType *this)
    We want:       void Foo::Foo()   (the caller handles this via ECX)

    Also strips __thiscall keyword since MSVC __thiscall is implicit for
    non-static member functions.
    """
    # Remove __thiscall keyword
    source = re.sub(r'\b__thiscall\b\s*', '', source)
    
    # Remove explicit (SomeType *this) or (SomeType * this) parameter
    # when it is the only parameter
    source = re.sub(r'\(\s*\w[\w\s\*]*\*\s*this\s*\)', '()', source)
    
    # Remove it when it is the first of multiple parameters:
    # (FooType *this, int x, ...) -> (int x, ...)
    source = re.sub(r'\(\s*\w[\w\s\*]*\*\s*this\s*,\s*', '(', source)

    # Remove explicit (this) parameter
    # when it is the only parameter
    source = re.sub(r'\(\s*\s*this\s*\)', '()', source)
    
    # Remove it when it is the first of multiple parameters:
    # (this, x, ...) -> (x, ...)
    source = re.sub(r'\(\s*\s*this\s*,\s*', '(', source)

    return source

def is_thiscall_function(func):
    """Heuristic: check if the function's calling convention is __thiscall."""
    if func is None:
        return False
    cc = func.getCallingConventionName()
    if cc is not None and '__thiscall' in cc:
        return True
    # Fallback: check parameter names for 'this'
    params = func.getParameters()
    for p in params:
        if p.getName() == 'this':
            return True
    return False

def process_dat_prefixes(decompiled_source):
    """
    Detect which DAT_<name> prefix is used for 'this' in the given source.

    Ghidra names the global after the struct type, e.g. DAT_TextManagerObject,
    DAT_TileMapStateObject, etc. We find all DAT_ tokens that are followed by
    a '.' (member access) — those are __thiscall this-references.

    Returns a list of (dat_prefix, struct_name) tuples found.
    """
    # Match DAT_Xxx.fieldName  (dot access = member of the object)
    pattern = re.compile(r'\b(DAT_\w+)\.(\w+)')
    matches = pattern.findall(decompiled_source)
    # Deduplicate, preserve order
    seen = {}
    result = decompiled_source
    for dat_name, field in matches:
        result = result.replace(dat_name + "." + field, dat_name + "::ptr->" + field)
    return result

def find_dat_includes(decompiled_source, globals_folder):
    pattern = re.compile(r'\b([A-Z]{3,}_\w+)[.\[]')
    matches = pattern.findall(decompiled_source)
    for match in matches:
        yield '#include "' + globals_folder +'/'+match+'.hpp"'

def fix_enum_namespaces(decompilation_result: DecompileResults, source: str):
    for block in decompilation_result.getHighFunction().getBasicBlocks():
        if not isinstance(block, PcodeBlockBasic):
            continue
        for part in block.getIterator():
            if not isinstance(part, PcodeOpAST):
                continue
            for input in part.getInputs():
                input = input.getHigh()
                if input:
                    if isinstance(input, HighConstant):
                        dt = input.getDataType()
                        if isinstance(dt, EnumDB): # type: ignore
                            for name in dt.getNames():
                                if name in source:
                                    if "::" + name in source:
                                        continue
                                    p = dt.getDataTypePath().getCategoryPath().getPath()
                                    while p.startswith("/"):
                                        p = p[1:]
                                    p = p.replace("/", "::")
                                    source = source.replace(name, p + "::" + name)
    return source


def guess_includes(decompilation_result: DecompileResults, globals_folder: str):
    inputs = []
    for block in decompilation_result.getHighFunction().getBasicBlocks():
        if not isinstance(block, PcodeBlockBasic):
            continue
        for part in block.getIterator():
            if not isinstance(part, PcodeOpAST):
                continue
            for input in part.getInputs():
                if input.getHigh():
                    inputs.append(input.getHigh())
    includes = []
    for input in inputs:
        data_type = input
        while hasattr(data_type, "getDataType"):
            data_type = data_type.getDataType()
        path = data_type.getDataTypePath()
        if path.getCategoryPath().getPath() != "/":
            path_string = path.getPath()
            if path_string and path_string not in includes:
                while path_string[0] == '/':
                    path_string = path_string[1:]
                if path_string not in includes:
                    includes.append(path_string)
        if (isinstance(input, HighGlobal) and input.getName()) and input.getName() != "UNNAMED":
            include = globals_folder + "/" + input.getName()
            if include not in includes:
                includes.append(include)
    return [f'#include "{include}.hpp"' for include in includes]


def preprocess(func, decompilation_result, source, toAddr, globals_folder, transformer = ("_HoldStrong", "OpenSHC")):
    """
    Full preprocessing pipeline for a single decompiled function source string.
    """
    result = fix_enum_namespaces(decompilation_result=decompilation_result, source=source)
    
    # 1. Strip Ghidra header comment block
    result = strip_ghidra_signature_comments(result)
    
    if is_thiscall_function(func):
        # 2. Detect all DAT_X.field this-references
        dat_prefix = get_thiscall_dat_prefix(func, toAddr)
    
        if dat_prefix:
            # 4. Replace DAT_X.field -> this->field
            result = replace_this_references(result, dat_prefix)
    
        # 5. Fix signature (remove __thiscall, explicit this param)
        result = fix_thiscall_param(result)
    
    # 6. Optionally annotate cross-object globals
    #if ANNOTATE_CDECL_GLOBALS:
    #    result = annotate_cdecl_globals(result)
    
    pns = func.getParentNamespace()
    isClass = pns.getSymbol().getSymbolType().CLASS == pns.getSymbol().getSymbolType()
    fname = func.getName(True).replace(*transformer)
    nsparts = fname.split("::")
    if isClass:
        nsparts = fname.split("::", fname.count("::") - 1)
    ns = pns.getName(True)
    nsp = ns.replace("::", "/").replace(*transformer) + ".hpp"
    includes = ['#include "' + nsp + '"']
    includes += [inc.replace(*transformer) for inc in guess_includes(decompilation_result=decompilation_result, globals_folder=globals_folder)]
    includes += list(find_dat_includes(result, globals_folder=globals_folder))
    namespace_wrap_start = ["namespace "+ nsparts[i] + " {" for i in range(len(nsparts) - 1)]
    namespace_wrap_end = ["}"] * (len(nsparts) - 1)
    result = process_dat_prefixes(result).replace(*transformer)
    result = '\n'.join(sorted(set(includes))) + '\n\n' + '\n'.join([*namespace_wrap_start, result, *namespace_wrap_end])
    lines = result.splitlines(keepends=False)
    index = -1
    for i, line in enumerate(lines):
        if fname in line:
            index = i
            break
    else:
        result = result.replace(fname, nsparts[-1])
        return result
    lines[index] = lines[index].replace(fname, nsparts[-1])
    lines[index-1] = f'// FUNCTION: STRONGHOLDCRUSADER 0x{func.getEntryPoint().getUnsignedOffset():0{8}x}'
    result = '\n'.join(lines)
    return result


