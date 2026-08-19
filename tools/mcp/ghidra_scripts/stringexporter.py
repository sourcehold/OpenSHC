#This script exports .rdata literal strings and addresses into a file. 
# Labels are either default Ghidra labels or labels set by users.
#@author Gynt
#@category _OPENSHC.TOOLS.DECOMPILATION
#@keybinding 
#@menupath 
#@toolbar 
#@runtime Jython

from ghidra.program.model.data import Array
import re
PATTERN = re.compile("[^a-zA-Z0-9_]+")


l = getCurrentProgram().getListing()
roRange = getCurrentProgram().getMemory().getBlocks()[2].getAddressRange()

sdump = "#pragma once\n\n"

cur = l.getCodeUnitAt(roRange.getMinAddress())
while cur.getAddress() < roRange.getMaxAddress():
	while True:
		if cur.getDataType().toString() == "string":
			break;
		if isinstance(cur.getDataType(), Array):
			if cur.getDataType().getDataType().toString() == "char":
				break;
		cur = l.getCodeUnitAfter(cur.getAddress())
	try:
		if cur.getLabel():
			sdump += "// STRING: STRONGHOLDCRUSADER 0x00" + hex(cur.getAddress().getOffset())[2:-1] + "\n"
			sdump += "char const * const " + PATTERN.sub("_", cur.getLabel()) + ' = "' + cur.getValue().replace("\\", "\\\\").replace("\n", "\\n").replace("\r", "\\r").replace('"', '\\"') + '";' + "\n\n"
	except Exception as e:
		print("failed at: " + cur.getAddress().toString())
	cur = l.getCodeUnitAfter(cur.getAddress())

with open(str(askFile("dump file", "select")), "w") as f:
	f.write(sdump)
