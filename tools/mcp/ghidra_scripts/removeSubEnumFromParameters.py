#TODO write a description for this script
#@author 
#@category _OPENSHC
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra

if __name__ == "__main__":
	#import ghidra.program.database.data.EnumDB
	import ghidra.program.model.symbol.SourceType

	dtm = getCurrentProgram().getDataTypeManager()

	fs = [f for f in getCurrentProgram().getFunctionManager().getFunctions(False) if f.getPathList(True)[0] == "_HoldStrong"]
	params = [p for f in fs for p in f.getParameters() if p.getDataType().__class__.__name__.endswith("EnumDB")]
	for param in params:
		dt = param.getDataType()
		dtp = dt.getDataTypePath().toString()
		for suffix in ["Int", "Short", "Byte"]:
			if dtp.endswith(suffix):
				dtp = dtp[:-len(suffix)]
				dtr = dtm.getDataType(dtp)
				if not dtr:
					print(f"no root enum for: {param.getFunction().getSignature().toString()}")
				else:
					print(f"setting enum for: {param.getFunction().getSignature().toString()}")
					param.setDataType(dtr, ghidra.program.model.symbol.SourceType.USER_DEFINED)
					print(f"successfully set enum for: {param.getFunction().getSignature().toString()}")
				break

	fs = [f for f in getCurrentProgram().getFunctionManager().getFunctions(False) if f.getPathList(True)[0] == "_HoldStrong"]
	rets = [f.getReturn() for f in fs if f.getReturn().getDataType().__class__.__name__.endswith("EnumDB")]
	for ret in rets:
		dt = ret.getDataType()
		dtp = dt.getDataTypePath().toString()
		for suffix in ["Int", "Short", "Byte"]:
			if dtp.endswith(suffix):
				dtp = dtp[:-len(suffix)]
				dtr = dtm.getDataType(dtp)
				if not dtr:
					print(f"no root enum for: {ret.getFunction().getSignature().toString()}")
				else:
					print(f"setting enum for: {ret.getFunction().getSignature().toString()}")
					ret.setDataType(dtr, ghidra.program.model.symbol.SourceType.USER_DEFINED)
					print(f"successfully set enum for: {ret.getFunction().getSignature().toString()}")
				break