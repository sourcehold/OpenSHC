#TODO write a description for this script
#@author 
#@category _OPENSHC.TOOLS
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


#TODO Add User Code Here

l = getCurrentProgram().getListing()
ECX = getCurrentProgram().getLanguage().getRegisters()[1]
fs = [f for f in getCurrentProgram().getFunctionManager().getFunctions(True) if f.getPathList(True)[0] == "_HoldStrong" and f.getCallingConvention().getName().startswith("__thiscall")]

ecxs = {}

for f in fs:
	cu = l.getCodeUnitAt(f.getEntryPoint())
	rv = cu.getRegisterValue(ECX)
	if rv:
		ns = f.getParentNamespace()
		if ns in ecxs:
			if ecxs[ns] != rv.getUnsignedValue():
				print("invalid ecx in function: " + str(f))
		else:
			ecxs[ns] = rv.getUnsignedValue()
