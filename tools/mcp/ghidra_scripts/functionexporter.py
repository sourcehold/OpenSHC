# Export Decompiled Code for _HoldStrong Namespace (Recursive, one file per function)
# Ghidra 11.4.1 - Python 3 (Jython bridge via GhidraScript)
#
# Output layout:
#   Given function _HoldStrong::A::B(), the decompiled code is written to:
#     <OUTPUT_ROOT>/_HoldStrong/A/B.cpp
#
# Usage:
#   1. Open your binary in Ghidra and run auto-analysis.
#   2. Go to Window > Script Manager > Run Script, select this file.
#   3. Files are written under OUTPUT_ROOT (default: a folder named after the
#      program, placed next to this script).
#
# @author  Claude
# @category _OPENSHC.TOOLS.DECOMPILATION
# @keybinding
# @menupath
# @toolbar
# @runtime PyGhidra

import typing
if typing.TYPE_CHECKING:
    from ghidra.ghidra_builtins import * # type: ignore

import os
import re
from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.model.symbol import SymbolType



TARGET_NAMESPACE  = "_HoldStrong"  # Root namespace to search (case-sensitive)
OUTPUT_ROOT       = None           # None <script_dir>/<program_name>_decompiled/
TIMEOUT_SECONDS   = 60             # Per-function decompile timeout
INCLUDE_SIGNATURE = True           # Prepend the function signature as a comment
RECURSIVE         = True           # Descend into child namespaces

currentProgram = getCurrentProgram()


def get_output_root():
    """Return (and create if needed) the root output directory."""
    if OUTPUT_ROOT:
        root = OUTPUT_ROOT
    else:
        #prog_name = re.sub(r'[^\w\-.]', '_', currentProgram.getName())
        script_dir = os.path.dirname(os.path.abspath(
            getScriptName() if hasattr(__builtins__, 'getScriptName') else __file__))
        root = os.path.join(script_dir, "decompilation")
    if not os.path.isdir(root):
        os.makedirs(root)
    return root


def sanitize_path_component(name):
    """
    Make a single namespace / function name safe for use as a file-system
    component.  Replaces characters that are illegal on Windows/Linux/macOS.
    Operator names like 'operator+=' become 'operator_plus_eq_' etc.
    """
    replacements = [
        ('::', '__'),
        ('<', '_lt_'), ('>', '_gt_'),
        ('*', '_star_'), ('/', '_div_'), ('%', '_mod_'),
        ('+', '_plus_'), ('-', '_minus_'),
        ('&', '_amp_'), ('|', '_pipe_'), ('^', '_xor_'), ('~', '_tilde_'),
        ('!', '_not_'), ('=', '_eq_'),
        ('(', '_'), (')', '_'), (',', '_'), (' ', '_'),
        ('[', '_'), (']', '_'),
    ]
    for old, new in replacements:
        name = name.replace(old, new)
    name = re.sub(r'[^\w\-.]', '_', name)
    name = re.sub(r'_+', '_', name).strip('_')
    return name or '_unnamed_'


def ns_path_to_file_path(output_root, ns_qualified_name, func_name):
    """
    Convert a fully-qualified namespace path and function name into a file path.

    Example:
        ns_qualified_name = "_HoldStrong::A"
        func_name         = "B"
        <output_root>/_HoldStrong/A/B.cpp
    """
    # Split on '::' to get each namespace component
    parts = [p for p in ns_qualified_name.split('::') if p]
    if parts[0] == "_HoldStrong":
        parts[0] = "OpenSHC"
    parts.append(func_name)                  # function name becomes the filename
    safe_parts = [sanitize_path_component(p) for p in parts]
    dir_parts  = safe_parts[:-1]
    file_part  = safe_parts[-1] + '.cpp'
    out_dir    = os.path.join(output_root, *dir_parts) if dir_parts else output_root
    if not os.path.isdir(out_dir):
        os.makedirs(out_dir)
    return os.path.join(out_dir, file_part)


def init_decompiler():
    """Initialise and open a DecompInterface for the current program."""
    iface = DecompInterface()
    opts  = DecompileOptions()
    iface.setOptions(opts)
    iface.openProgram(currentProgram)
    return iface


def decompile_function(func, iface, monitor):
    """Return (code_str, None) on success or (None, error_str) on failure."""
    result = iface.decompileFunction(func, TIMEOUT_SECONDS, monitor)
    if result is None or not result.decompileCompleted():
        err = result.getErrorMessage() if result else "unknown error"
        return None, "/* ERROR decompiling {}: {} */\n".format(func.getName(), err)
    markup = result.getDecompiledFunction().getC() # .getCCodeMarkup()
    if markup is None:
        return None, "/* ERROR: no C markup for {} */\n".format(func.getName())
    return str(markup).replace("_HoldStrong", "OpenSHC"), None


def collect_functions_in_namespace(ns):
    """
    Recursively collect every Function symbol inside *ns* and its descendants.

    Returns a list of (ns_qualified_name, Function) tuples where
    ns_qualified_name is the namespace the function belongs to (NOT including
    the function name itself), e.g. "_HoldStrong::A".
    """
    results   = []
    sym_table = currentProgram.getSymbolTable()
    ns_name   = ns.getName(True)   # fully-qualified, e.g. "_HoldStrong::A"

    children = sym_table.getChildren(ns.getSymbol())
    while children.hasNext():
        sym = children.next()
        sym_type = sym.getSymbolType()

        if sym_type == SymbolType.FUNCTION:
            func = getFunctionAt(sym.getAddress())
            if func is not None:
                results.append((ns_name, func))

        elif RECURSIVE and sym_type in (SymbolType.NAMESPACE, SymbolType.CLASS):
            child_ns = sym.getObject()
            if child_ns is not None:
                results.extend(collect_functions_in_namespace(child_ns))

    return results


def find_root_namespace(name):
    """
    Find the first namespace (or class) whose simple name matches *name*.
    Returns the Namespace object, or None if not found.
    """
    sym_table = currentProgram.getSymbolTable()
    it = sym_table.getSymbols(name)
    while it.hasNext():
        sym = it.next()
        if sym.getSymbolType() in (SymbolType.NAMESPACE, SymbolType.CLASS):
            return sym.getObject()
    return None



def run():
    monitor = ConsoleTaskMonitor()

    print("[*] Searching for namespace: {}".format(TARGET_NAMESPACE))
    root_ns = find_root_namespace(TARGET_NAMESPACE)
    if root_ns is None:
        msg = "Namespace '{}' not found in program.".format(TARGET_NAMESPACE)
        print("[!] " + msg)
        popup(msg)
        return

    print("[*] Found namespace: {}".format(root_ns.getName(True)))
    print("[*] Collecting functions{}...".format(
        " recursively" if RECURSIVE else ""))

    entries = collect_functions_in_namespace(root_ns)
    if not entries:
        msg = "No functions found under '{}'.".format(TARGET_NAMESPACE)
        print("[!] " + msg)
        popup(msg)
        return

    print("[*] Found {} function(s). Decompiling...".format(len(entries)))

    iface       = init_decompiler()
    output_root = get_output_root()
    error_count = 0
    written     = []

    for idx, (ns_qualified, func) in enumerate(entries, 1):
        addr      = func.getEntryPoint()
        func_name = func.getName()
        out_path  = ns_path_to_file_path(output_root, ns_qualified, func_name)

        print("  [{}/{}] {}::{}  @{}".format(
            idx, len(entries), ns_qualified, func_name, addr))
        print("          -> {}".format(out_path))

        code, err = decompile_function(func, iface, monitor)

        with open(out_path, 'w', encoding='UTF-8') as fh:
            fh.write("// {}\n".format("=" * 76))
            fh.write("// Program   : {}\n".format(currentProgram.getName()))
            fh.write("// Namespace : {}\n".format(ns_qualified))
            fh.write("// Function  : {}\n".format(func_name))
            fh.write("// Address   : {}\n".format(addr))
            if INCLUDE_SIGNATURE:
                fh.write("// Signature : {}\n".format(func.getSignature()))
            fh.write("// {}\n\n".format("=" * 76))

            if err is not None:
                fh.write(err + "\n")
                error_count += 1
                print("    [!] " + err.strip())
            else:
                if not code:
                    raise Exception("impossible situation")
                fh.write(code)
                fh.write("\n")

        written.append(out_path)

    iface.dispose()

    summary = (
        "[+] Done. {} file(s) written, {} error(s).\n"
        "    Output root: {}"
    ).format(len(written), error_count, output_root)
    print(summary)
    popup(summary)

if __name__ == "__main__":
    # Ghidra calls run() automatically when the script is executed.
    run()
