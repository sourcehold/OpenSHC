#TODO write a description for this script
#@author 
#@category _OPENSHC.TOOLS
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


#TODO Add User Code Here

l = getCurrentProgram().getListing()
fm = getCurrentProgram().getFunctionManager()
def getContainingNamespace(f):
	return list(f.getPathList(True))[:-1]
def getFunctionAt(addr):
	return fm.getFunctionAt(addr)
def getFunctionReferencesTo(f):
	cu = l.getCodeUnitAt(f.getEntryPoint())
	return list(fm.getFunctionContaining(ref.getFromAddress()) for ref in cu.getReferenceIteratorTo())
def countNamespaces(fs):
	ns = set()
	for f in fs:
		if not f:
			ns.add("<error") # forcing a no answer
			continue
		ns.add("/".join(getContainingNamespace(f)))
	return ns
def getFunctionsInCurrentSelection():
	result = []
	for ar in currentSelection.getAddressRanges():
		result.append(getFunctionAt(ar.getMinAddress()))
	return result
def isFunctionPrivate(f):
	return len(countNamespaces(getFunctionReferencesTo(f) + [f])) == 1
def tagAllFunctionsAsPrivateOrPublic():
	classes = set()
	for ns in getCurrentProgram().getSymbolTable().getClassNamespaces():
		classes.add("/".join(ns.getPathList(True)))
	fs = fm.getFunctions(True)
	for f in fs:
		if "/".join(getContainingNamespace(f)) in classes:
			if isFunctionPrivate(f):
				if not "private" in f.getTags():
					if "public" in f.getTags():
						f.removeTag("public")
					f.addTag("private")
			else:
				if not "public" in f.getTags():
					if "private" in f.getTags():
						f.removeTag("private")
					f.addTag("public")
if __name__ == "__main__":
	tagAllFunctionsAsPrivateOrPublic()