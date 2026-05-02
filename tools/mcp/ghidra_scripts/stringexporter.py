#This script exports .rdata literal strings and addresses into a file. 
# Labels are either default Ghidra labels or labels set by users.
#@author Gynt
#@category _OPENSHC.TOOLS.DECOMPILATION
#@keybinding 
#@menupath 
#@toolbar 
#@runtime Jython



import re
PATTERN = re.compile("[^a-zA-Z0-9_]+")


l = getCurrentProgram().getListing()
roRange = getCurrentProgram().getMemory().getBlocks()[2].getAddressRange()

sdump = ""

cur = l.getCodeUnitAt(roRange.getMinAddress())
while cur.getAddress() < roRange.getMaxAddress():
	while cur.getDataType().toString() != "string":
		cur = l.getCodeUnitAfter(cur.getAddress())
	if cur.getLabel():
		sdump += "// STRING: STRONGHOLDCRUSADER 0x00" + hex(cur.getAddress().getOffset())[2:-1] + "\n"
		sdump += "char const * const " + PATTERN.sub("_", cur.getLabel()) + ' = "' + cur.getValue().replace("\\", "\\\\").replace("\n", "\\n").replace("\r", "\\r").replace('"', '\\"') + '";' + "\n\n"
	cur = l.getCodeUnitAfter(cur.getAddress())

with open(str(askFile("dump file", "select")), "w") as f:
	f.write(sdump)
