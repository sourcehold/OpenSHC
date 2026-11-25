#TODO write a description for this script
#@author 
#@category _OPENSHC.TOOLS
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


#TODO Add User Code Here

from ghidra.program.model.data import CategoryPath

dtm = getCurrentProgram().getDataTypeManager()

dtm.getAllStructures()

structs = [s for s  in dtm.getAllStructures() if s.getDataTypePath().getPath().startswith("/_HoldStrong")]

#s = structs[11]

for s in structs:
	components = s.getComponents()
	undefined_fields = [c for c in components if c.getFieldName() is None]
	for undefined_field in undefined_fields:
		field_name = f"field_{hex(undefined_field.getOffset())}"
		undefined_field.setFieldName(field_name)