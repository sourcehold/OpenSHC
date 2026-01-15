import typing
if typing.TYPE_CHECKING:
    from ghidra.ghidra_builtins import * # type: ignore

from pyghidra.script import get_current_interpreter
getCurrentProgram = get_current_interpreter().getCurrentProgram # type: ignore

import traceback
from http.server import BaseHTTPRequestHandler, HTTPServer
import json
import threading
import urllib
from urllib.parse import urlparse, parse_qs
from ghidra.app.decompiler import DecompInterface, DecompileOptions # type: ignore
from ghidra.util.task import ConsoleTaskMonitor # type: ignore
from ghidra.program.model.listing import Function # type: ignore
from ghidra.program.model.pcode import HighSymbol # type: ignore
import re

def decompile_function(func: Function, NAMESPACE = "EXE"):
    """
    Decompile a function using Ghidra's decompiler.
    
    Args:
        func: Ghidra Function object
    
    Returns:
        Dictionary with decompilation results
    """
    decompiler = None
    try:
        # Initialize decompiler
        decompiler = DecompInterface()
        decompiler.openProgram(getCurrentProgram())
        
        # Set decompiler options
        options = DecompileOptions()
        decompiler.setOptions(options)
        
        # Set a reasonable timeout
        decompiler.setSimplificationStyle("decompile")
        
        # Decompile
        monitor = ConsoleTaskMonitor()
        results = decompiler.decompileFunction(func, 30, monitor)  # 30 second timeout
        
        if results and results.decompileCompleted():
            decompiled_code = results.getDecompiledFunction().getC()

            highF = results.getHighFunction()

            global_symbols = list[HighSymbol](highF.getGlobalSymbolMap().getSymbols())

            clean_instructions: list[tuple[str, str]] = []
            includes: list[str] = []
            serialized_global_symbols = []
            for sym in global_symbols:
                dt = sym.getDataType()
                dtp = dt.getDataTypePath().getPath()
                dtn = dt.getName()
                if dtp[0] == '/':
                    dtp = dtp[1:]
                if dtp.startswith("_HoldStrong/"):
                    dtp = NAMESPACE + "/" + dtp[1+len("HoldStrong/"):]
                    includes.append(dtp.replace("/", "::") + ".hpp")
                    is_this = dtn in func.getName(True) # type: ignore
                    if hasattr(dt, "getNumElements"):
                        clean_instructions.append(("(?<!p)" + sym.getName() + "[.]", "(*p" + sym.getName() + "::ptr)->"))
                        clean_instructions.append(("(?<!p)" + sym.getName(), "(*p" + sym.getName() + "::ptr)"))
                    else:
                        if is_this:
                            clean_instructions.append(("(?<!p)" + sym.getName() + "[.]", "this->"))
                            clean_instructions.append(("&" + sym.getName(), "this"))
                        else:
                            clean_instructions.append(("(?<!p)" + sym.getName() + "[.]", "p" + sym.getName() + "::ptr->"))
                            clean_instructions.append(("(?<!p)" + sym.getName(), "p" + sym.getName() + "::ptr"))
                serialized_global_symbols.append({
                    "name": sym.getName(),
                    "type": dtp,
                })

            local_symbols = list[HighSymbol](highF.getLocalSymbolMap().getSymbols())
            for sym in local_symbols:
                dt = sym.getDataType()
                while hasattr(dt, "getDataType"):
                    dt = dt.getDataType()
                dtp = dt.getDataTypePath().getPath()
                if dtp[0] == '/':
                    dtp = dtp[1:]
                if dtp.startswith("_HoldStrong/"):
                    dtp = NAMESPACE + "/" + dtp[1+len("HoldStrong/"):]
                    includes.append(dtp.replace("/", "::") + ".hpp")

            # TODO: stub ADJ() using templates? https://stackoverflow.com/questions/34511712/using-offsetof-to-get-owner-object-from-member-variable
            print(clean_instructions)
            cleaned_code = decompiled_code.replace("_HoldStrong", NAMESPACE)
            for target, replacement in clean_instructions:
                cleaned_code = re.sub(pattern=target, repl=replacement, string=cleaned_code)
                #cleaned_code = cleaned_code.replace(target, replacement)
            
            return {
                "success": True,
                "function_name": func.getName(True), # type: ignore
                "function_short_name": func.getName(),
                "address": "0x" + func.getEntryPoint().toString(),
                "signature": func.getSignature().getPrototypeString(),
                "raw_decompiled_code": decompiled_code.replace("_HoldStrong", NAMESPACE),
                "decompiled_code": cleaned_code,
                "includes": list(set(includes)),
                "global_symbols": serialized_global_symbols,
                "language": "C",
                "calling_convention": str(func.getCallingConventionName()) if func.getCallingConventionName() else None
            }
        else:
            error_msg = "Decompilation did not complete"
            if results:
                error_msg = results.getErrorMessage()
            
            return {
                "success": False,
                "error": error_msg,
                "function_name": func.getName(),
                "address": "0x" + func.getEntryPoint().toString()
            }
    
    except Exception as e:
        return {
            "success": False,
            "error": "Decompilation exception: " + str(e) + ''.join(traceback.format_tb(e.__traceback__)),
            "function_name": func.getName() if func else "unknown",
            "address": "0x" + func.getEntryPoint().toString() if func else "unknown"
        }
    finally:
        if decompiler:
            decompiler.dispose()