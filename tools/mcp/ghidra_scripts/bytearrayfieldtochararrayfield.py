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

struct = dtm.getDataType(askString("Which datatype", "Full data type path such as: '/_HoldStrong/Map/AnimationFrameData'"))

print(struct)

comps = list(struct.getComponents())
comps = [c for c in comps if str(c.getDataType()).startswith("byte[")]
#comps = [c for c in comps if c.getFieldName() and (c.getFieldName() is None or "anim" in c.getFieldName().lower() or c.getFieldName().startswith("field_0x"))]

print(comps)

transID = dtm.startTransaction("convert byte[] to char[]")
status = False
try:
	for comp in comps:
		arr = ArrayDataType(dtm.getDataType("/char"), comp.getDataType().getNumElements())
		comp.setDataType(arr)
	status = True
	print("Success!")
except Exception as e:
	print(e)
	status = False

dtm.endTransaction(transID, status)
