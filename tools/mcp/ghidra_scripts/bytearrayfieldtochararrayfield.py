#TODO write a description for this script
#@author 
#@category _OPENSHC.TOOLS
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


#TODO Add User Code Here

from ghidra.program.model.data import ArrayDataType

dtm = getCurrentProgram().getDataTypeManager()

struct = dtm.getDataType("/_HoldStrong/Map/Buildings/BuildingDefinedData")

comps = list(struct.getComponents())
comps = [c for c in comps if c.getFieldName() and (c.getFieldName() is None or "Anim" in c.getFieldName()) and str(c.getDataType()).startswith("byte[")]

transID = dtm.startTransaction("convert byte[] to char[]")
status = False
try:
	for comp in comps:
		arr = ArrayDataType(dtm.getDataType("/char"), comp.getDataType().getNumElements())
		comp.setDataType(arr)
	status = True
except:
	status = False

dtm.endTransaction(transID, status)
