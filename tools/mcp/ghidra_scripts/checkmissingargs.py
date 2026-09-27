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

def get_ret_args(f):
	cu = l.getCodeUnitContaining(f.getBody().getLastRange().getMaxAddress())
	if str(cu).startswith("JMP"):
		return None
	if not str(cu).startswith("RET"):
		raise Exception(f"{f}: {cu}")
	if str(cu) == "RET":
		return 0 # No args
	return int(str(cu).split(" ")[-1], 16) // 4

def get_nargs(f):
	return -1 + len(f.getParameters())

for f in fs:
	ra = get_ret_args(f)
	pa = get_nargs(f)
	if ra != None and pa != None and ra - pa > 0:
		print(f"{f}: missing function parameters: {ra} {pa}")
	if ra != None and pa != None and ra - pa < 0:
		print(f"{f}: too many function parameters: {ra} {pa}")