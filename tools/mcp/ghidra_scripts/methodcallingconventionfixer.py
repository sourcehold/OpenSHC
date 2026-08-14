#TODO write a description for this script
#@author 
#@category _OPENSHC.TOOLS
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


#TODO Add User Code Here

from ghidra.program.model.listing import GhidraClass
fm = getCurrentProgram().getFunctionManager()
fs = [f for f  in fm.getFunctions(True) if f.getPathList(True)[0] == "_HoldStrong" and isinstance(f.getParentNamespace(), GhidraClass)]

misf = [f for f in fs if not f.getCallingConvention().getName().startswith("__thiscall")]