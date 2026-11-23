#TODO write a description for this script
#@author 
#@category _OPENSHC.TOOLS
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


#TODO Add User Code Here
from ghidra.app.decompiler import DecompInterface, DecompileOptions
from ghidra.util.task import ConsoleTaskMonitor
import re

TARGET_NAMESPACE  = "_HoldStrong"  # Root namespace to search (case-sensitive)
OUTPUT_ROOT       = None           # None <script_dir>/<program_name>_decompiled/
TIMEOUT_SECONDS   = 60             # Per-function decompile timeout
INCLUDE_SIGNATURE = True           # Prepend the function signature as a comment
RECURSIVE         = True           # Descend into child namespaces

fs = [f for f in getCurrentProgram().getFunctionManager().getFunctions(True) if f.getPathList(True)[0] == "_HoldStrong"]

def init_decompiler():
    """Initialise and open a DecompInterface for the current program."""
    iface = DecompInterface()
    opts  = DecompileOptions()
    opts.setNoCastPrint(False)
    opts.setEliminateUnreachable(False)
    opts.setPLATECommentIncluded(True)
    opts.setPOSTCommentIncluded(True)
    opts.setPRECommentIncluded(True)
    opts.setEOLCommentIncluded(True)
    opts.setHeadCommentIncluded(True)
    
    iface.setOptions(opts)
    iface.openProgram(currentProgram)
    return iface


def decompile_function(func, iface, monitor):
    """Return (result, code_str, None) on success or (None, error_str) on failure."""
    result = iface.decompileFunction(func, TIMEOUT_SECONDS, monitor)
    if result is None or not result.decompileCompleted():
        err = result.getErrorMessage() if result else "unknown error"
        return None, "/* ERROR decompiling {}: {} */\n".format(func.getName(), err)
    markup = result.getDecompiledFunction().getC() # .getCCodeMarkup()
    if markup is None:
        return None, None, "/* ERROR: no C markup for {} */\n".format(func.getName())
    return result, str(markup).replace("_HoldStrong", "OpenSHC"), None

def should_be_bool_enum(src):
    rets = re.findall("(return[^;]*)", src)
    matches = [r for r in rets if r == "return 0" or r == "return 1"]
    if len(matches) == len(rets):
         return True
    return False

INTERFACE = init_decompiler()

import ghidra.program.model.symbol.SourceType
UD = ghidra.program.model.symbol.SourceType.USER_DEFINED