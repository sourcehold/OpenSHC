#TODO write a description for this script
#@author 
#@category _OPENSHC
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


#TODO Add User Code Here

l = getCurrentProgram().getListing()
fm = getCurrentProgram().getFunctionManager()

fs = [f for f in fm.getFunctions(True) if f.getPathList(True)[0] == "_HoldStrong" and "thiscall" in f.getCallingConvention().getName()]

for f in fs:
	if "cdecl" in f.getCallingConvention().getName():
		if f.getName()[0] == f.getName()[0].lower():
			print(f"{f}: wrong capitalization")
	if "thiscall" in f.getCallingConvention().getName():
		if f.getName()[0] == f.getName()[0].upper() and not f.getName().startswith("Constructor"):
			print(f"{f}: wrong capitalization")