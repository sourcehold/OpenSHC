#TODO write a description for this script
#@author 
#@category _OPENSHC.TOOLS.DECOMPILATION
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


l = getCurrentProgram().getListing()
fm = getCurrentProgram().getFunctionManager()

def find_mov_ecx(cu, search_range = 25, permit_jumps = 3, permit_backward_jumps = False, distance_confidence = 1):
	original_cu = cu
	root_f = fm.getFunctionContaining(cu.getAddress())
	found_mov_ecx = False
	for i in range(search_range):
		for ref in cu.getReferenceIteratorTo():
			if permit_jumps > 0 and "JUMP" in ref.getReferenceType().toString():
				if not permit_backward_jumps and ref.getFromAddress() > ref.getToAddress():
					continue # no backward jumps
				jump_origin_result = find_mov_ecx(l.getCodeUnitAt(ref.getFromAddress()), permit_jumps=permit_jumps - 1)
				if jump_origin_result[0] == True:
					return jump_origin_result[0], jump_origin_result[1], jump_origin_result[2]
		cu = cu.getPrevious()
		cus = cu.toString()
		f = fm.getFunctionContaining(cu.getAddress())
		if f != root_f:
			break
		if cus.startswith("CALL "):
			break
		if cus.startswith("MOV ECX,"):
			if cus.startswith("MOV ECX,0x"):
				found_mov_ecx = True
				break
			elif distance_confidence - i > 0:
				found_mov_ecx = True # guess that it is a true mov ecx
				break
			elif cus.startswith("MOV ECX,ESI") or cus.startswith("MOV ECX,EDI") or cus.startswith("MOV ECX,EBX") or cus.startswith("MOV ECX,EBP"):
				found_mov_ecx = True # less confident
				break
			break # likely ECX is clobbered

			
	return found_mov_ecx, cu.getAddress(), cu

def find_mov_ecx_in_calls_to_thiscall_function(f):
	if not f.getCallingConvention().toString().startswith("__thiscall"):
		raise Exception()
	cu = l.getCodeUnitAt(f.getEntryPoint())
	for ref in cu.getReferenceIteratorTo():
		if ref.getReferenceType().toString() != "UNCONDITIONAL_CALL":
			continue
		addr_from = ref.getFromAddress()
		cu_func = fm.getFunctionContaining(addr_from)
		if not cu_func:
			pass #	print("no function at: " + addr_from.toString())
		fcu = l.getCodeUnitAt(addr_from)
		if not fcu:
			print("no code unit at: " + addr_from.toString() + " " + ref.toString())
			continue
		yield f, cu_func, addr_from, find_mov_ecx(fcu)

if __name__ == "__main__":
	import csv
	path = askFile("Select file", "Save")
	with open(path.getPath(), 'w', newline='') as handle:
		csvwriter = csv.writer(handle, delimiter='\t', quotechar='"')
		csvwriter.writerow(["CalledFunction", "CallerFunction", "CrossRef", "Distance", "CallerLocation", "FoundMovECX", "Needle", "NeedleString"])
		fs = [f for f in fm.getFunctions(True) if f.getCallingConvention() and f.getCallingConvention().toString().startswith("__thiscall") and f.getPathList(True)[0] == "_HoldStrong"]
		for f in fs:
			interesting = False
			for needle in find_mov_ecx_in_calls_to_thiscall_function(f):
				d = "NA"
				crossref = False
				if needle[1]:
					d = hex(needle[1].getEntryPoint().getOffset() - needle[0].getEntryPoint().getOffset())
					if list(f.getPathList(True)[:-1]) != list(needle[1].getPathList(True)[:-1]):
						crossref = True
				csvwriter.writerow([needle[0], needle[1], crossref, d, hex(needle[2].getOffset()), needle[3][0], hex(needle[3][1].getOffset()), needle[3][2].toString()])
				print(needle[0], needle[1], d, needle[2], needle[3][0], needle[3][1], '"' + needle[3][2].toString() + '"')
