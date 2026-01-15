# MCP server

AI can be of help with increasing accuracy.

## Setup

In Ghidra, add the `ghidra_scripts` directory as a directory in the Script Manager window. Then launch `_OpenSHC/TOOLS/ghidra_server.py` from the Script Manager to start the server to expose Ghidra functionality to an MCP client such as Claude.

## Claude specific setup

Copy the file `claude_desktop_configuration.json` to your Claude directory (`%APPDATA%\Claude`) and adapt it such that it points to this mcp directory containing `decomphelper.py` on your file system. Restart Claude completely.
