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
pragma_once = """#pragma once

""" 
sdump = pragma_once + '#include "OpenSHC/string-macros.hpp"\n\n'
mdump = pragma_once + """#define S_GM "gm\\\\"

#define S_FX "fx\\\\"

"""

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
			s_label = PATTERN.sub("_", cur.getLabel())
			m_label = s_label.upper()
			v = cur.getValue().replace("\\", "\\\\").replace("\n", "\\n").replace("\r", "\\r").replace('"', '\\"')
			sdump += "// STRING: STRONGHOLDCRUSADER 0x00" + hex(cur.getAddress().getOffset())[2:-1] + "\n"
			sdump += "char const * const " + s_label + ' = ' + m_label + ';' + "\n\n"
			mdump += "// 0x00" + hex(cur.getAddress().getOffset())[2:-1] + "\n"
			mdump += "#define "+ m_label + '"' + v + '"' + "\n\n"
	except Exception as e:
		print("failed at: " + cur.getAddress().toString())
	cur = l.getCodeUnitAfter(cur.getAddress())

dir = askDirectory("Select output dir", "Choose")
with open(str(dir) + "/string-literals.hpp", "wb") as f:
	f.write(sdump)
with open(str(dir) + "/string-macros.hpp", "wb") as f:
	f.write(mdump)