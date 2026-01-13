#TODO write a description for this script
#@author Gynt
#@category _OPENSHC.TOOLS.MCP
#@keybinding 
#@menupath 
#@toolbar 
#@runtime PyGhidra


NAMESPACE = "OpenSHC"

"""
Starts an HTTP server that provides function decompilation via REST API.

Server runs on http://127.0.0.1:11337
Endpoint: POST /functions/decompile

Request body (JSON):
{
    "address": "0x004F8160",  // Function address (hex string)
    "name": "functionName"     // Alternative: function name
}

Response (JSON):
{
    "success": true,
    "function_name": "getBuildingHealthAtTileOr1000",
    "address": "0x004f8160",
    "signature": "int getBuildingHealthAtTileOr1000(int tile)",
    "decompiled_code": "...",
    "language": "C"
}
"""

from decompilation import decompile_function
print(decompile_function)

import typing
if typing.TYPE_CHECKING:
    from ghidra.ghidra_builtins import * # type: ignore

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

# Global server instance
server_thread = None
httpd: HTTPServer | None = None

KEEP_RUNNING = True

fm = getCurrentProgram().getFunctionManager()
fdb = {}
for f in fm.getFunctions(True):
    name = f.getName(True)
    fdb[name] = f
    if name.startswith("_HoldStrong::"):
        fdb[NAMESPACE + "::" + name[len("_HoldStrong::"):]] = f

class DecompilationHandler(BaseHTTPRequestHandler):
    """HTTP request handler for decompilation requests."""
    
    def log_message(self, format, *args):
        """Override to use Ghidra's println instead of stderr."""
        println("[Server] %s - - [%s] %s" % (
            self.client_address[0],
            self.log_date_time_string(),
            format % args
        ))
    
    def _set_headers(self, status=200, content_type='application/json'):
        """Set response headers."""
        self.send_response(status)
        self.send_header('Content-type', content_type)
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        self.end_headers()
    
    def _send_json(self, data, status=200):
        """Send JSON response."""
        self._set_headers(status)
        self.wfile.write(json.dumps(data, indent=2).encode("utf-8"))
    
    def _send_error_json(self, message, status=400):
        """Send error response."""
        self._send_json({
            "success": False,
            "error": message
        }, status)
    
    def do_OPTIONS(self):
        """Handle OPTIONS request for CORS."""
        self._set_headers()
    
    def do_GET(self):
        """Handle GET requests."""
        url = urlparse(self.path)
        path = url.path
        if path == '/':
            self._set_headers(content_type='text/html')
            html = """
            <!DOCTYPE html>
            <html>
            <head>
                <title>Ghidra Decompilation Server</title>
                <style>
                    body { font-family: Arial, sans-serif; margin: 40px; }
                    h1 { color: #333; }
                    .endpoint { background: #f4f4f4; padding: 10px; margin: 10px 0; }
                    code { background: #e0e0e0; padding: 2px 5px; }
                </style>
            </head>
            <body>
                <h1>Ghidra Decompilation Server</h1>
                <p>Server is running on port 11337</p>
                
                <h2>Available Endpoints:</h2>
                
                <div class="endpoint">
                    <h3>POST /functions/decompile</h3>
                    <p>Decompile a function by address or name</p>
                    <p><strong>Request body:</strong></p>
                    <pre>{
    "address": "0x004F8160",  // hex address
    // OR
    "name": "functionName"
}</pre>
                </div>
                
                <div class="endpoint">
                    <h3>GET /health</h3>
                    <p>Check server health status</p>
                </div>
            </body>
            </html>
            """
            self.wfile.write(html.encode("utf-8"))
        
        elif path == '/health':
            self._send_json({
                "status": "healthy",
                "program": str(currentProgram.getName()) if currentProgram else None
            })
        elif path == '/exit':
            self._send_json({"status": "shutdown", })
            KEEP_RUNNING = False
            monitor.cancel()
        elif path == '/functions/decompile':
            print(url)
            if not url.query:
                return self._send_error_json("no parameters", 400)
            qc = parse_qs(url.query)
            print(qc)
            if not "name" in qc:
                return self._send_error_json("parameter 'name' missing", 400)
            funcName = qc["name"][0]
            print(funcName)
            if funcName not in fdb:
                return self._send_error_json("not found: " + funcName, 404)
            # Decompile the function
            decompiled = self._decompile_function(fdb[funcName])
            
            if decompiled["success"]:
                self._send_json(decompiled)
            else:
                self._send_error_json(decompiled.get("error", "Decompilation failed"))            
        else:
            self._send_error_json("Not found", 404)
    
    def do_POST(self):
        """Handle POST requests."""
        if self.path == '/functions/decompile':
            try:
                # Read request body
                content_length = int(self.headers.get('Content-Length', 0))
                post_data = self.rfile.read(content_length)
                request_data = json.loads(post_data)
                
                # Get function address or name
                address_str = request_data.get('address')
                function_name = request_data.get('name')
                
                if not address_str and not function_name:
                    self._send_error_json("Either 'address' or 'name' must be provided")
                    return
                
                # Find function
                func = None
                if address_str:
                    # Parse address
                    if address_str.startswith('0x') or address_str.startswith('0X'):
                        address_str = address_str[2:]
                    
                    try:
                        addr = currentProgram.getAddressFactory().getAddress(address_str)
                        func = currentProgram.getFunctionManager().getFunctionAt(addr)
                    except:
                        self._send_error_json("Invalid address format: " + address_str)
                        return
                
                elif function_name:
                    # Search by name
                    function_manager = currentProgram.getFunctionManager()
                    functions = function_manager.getFunctions(True)  # Get all functions
                    for f in functions:
                        if f.getName() == function_name:
                            func = f
                            break
                
                if not func:
                    self._send_error_json("Function not found")
                    return
                
                # Decompile the function
                decompiled = self._decompile_function(func)
                
                if decompiled["success"]:
                    self._send_json(decompiled)
                else:
                    self._send_error_json(decompiled.get("error", "Decompilation failed"))
                
            except json.JSONDecodeError:
                self._send_error_json("Invalid JSON in request body")
            except Exception as e:
                self._send_error_json("Internal server error: " + str(e), 500)
        
        else:
            self._send_error_json("Not found", 404)
    
    def _decompile_function(self, func: Function):
        return decompile_function(func, NAMESPACE=NAMESPACE)


def serve(threaded = False):
    while not monitor.cancelled:
        if not httpd:
            break
        httpd.handle_request()
        if not threaded:
            if not KEEP_RUNNING:
                break
    stop_server()

def start_server(threaded=False):
    """Start the HTTP server in a background thread."""
    global server_thread, httpd
    
    if server_thread and server_thread.is_alive():
        println("[Server] Server is already running on port 11337")
        return
    
    try:
        server_address = ('127.0.0.1', 11337)
        httpd = HTTPServer(server_address, DecompilationHandler)
        httpd.timeout = 1
        
        println("[Server] Starting Ghidra Decompilation Server on http://127.0.0.1:11337")
        println("[Server] Endpoint: POST http://127.0.0.1:11337/functions/decompile")
        println("[Server] Press Ctrl+C in console or run 'Stop Decompilation Server' to stop")
        println("[Server] Visit http://127.0.0.1:11337 in your browser for API documentation")
        
        if threaded:
                # Run server in background thread
                server_thread = threading.Thread(target=serve)
                server_thread.daemon = True
                server_thread.start()
                println("[Server] Server started successfully!")
        else:
                println("[Server] Serving...")
                serve()
                
    except Exception as e:
        println("[Server] Failed to start server: " + str(e))
        if "Address already in use" in str(e):
            println("[Server] Port 11337 is already in use. Stop the existing server first.")


def stop_server(threaded = False):
    """Stop the HTTP server."""
    global httpd, server_thread
    
    if httpd:
        println("[Server] Stopping server...")
        if threaded:
            httpd.shutdown()
        httpd.server_close()
        httpd = None
        server_thread = None
        println("[Server] Server stopped.")
    else:
        println("[Server] No server is currently running.")


# Main execution
if __name__ == '__main__':
    if not currentProgram:
        println("[Server] Error: No program is currently open in Ghidra")
        println("[Server] Please open a program before starting the server")
    else:
        start_server()
