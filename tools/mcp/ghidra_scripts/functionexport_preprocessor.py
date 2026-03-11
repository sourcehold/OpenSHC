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

def find_dat_includes(decompiled_source):
    pattern = re.compile(r'\b([A-Z]{3,}_\w+)[.\[]')
    matches = pattern.findall(decompiled_source)
    for match in matches:
        yield '#include "OpenSHC/'+match+'.hpp"'
        

def preprocess(func, source, toAddr):
    """
    Full preprocessing pipeline for a single decompiled function source string.
    """
    result = source
    
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
    
    ns = func.getParentNamespace().getName(True)
    nsp = ns.replace("::", "/") + ".hpp"
    result = '#include "'+nsp+'"\n\n' + result
    
    result = "\n".join(find_dat_includes(result)) + result
    
    return process_dat_prefixes(result).replace("_HoldStrong", "OpenSHC")


