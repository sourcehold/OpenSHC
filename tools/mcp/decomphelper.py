#!/usr/bin/env python3
"""
MCP Server for C++ decompilation and assembly comparison tasks.

This server provides tools for:
- Compiling C++ files with MSVC
- Comparing assembly output with target assembly
- Generating assembly diffs

Usage:
    Claude:
        add a mcpServers entry to the Claude Desktop App config file
    Testing:
        python decomp_mcp_server.py
"""

import asyncio
import json
import os
import subprocess
import tempfile
from pathlib import Path
from typing import Any, Sequence
import difflib
import re
import sys
import requests
#sys.stdout.reconfigure(line_buffering=True)
#sys.stderr.reconfigure(line_buffering=True)
import logging
logging.basicConfig(stream=sys.stderr)

from mcp.server.fastmcp import FastMCP
from mcp.types import (
    Resource,
    Tool,
    TextContent,
    ImageContent,
    EmbeddedResource,
    LoggingLevel
)
import mcp.server.stdio

PATH_CMAKE_OPENSHC_SOURCES = Path("cmake/openshc-sources.txt")
if not PATH_CMAKE_OPENSHC_SOURCES.exists():
    raise Exception(f"could not find cmake core sources txt file: {str(PATH_CMAKE_OPENSHC_SOURCES)}")

# Initialize MCP server
mcp = FastMCP("decomp-helper")

def compile_project() -> tuple[bool, str, str]:
    """
    Compile the C++ project using MSVC. Must be executed after writing new cpp file contents.
    
    Returns:
        Tuple of (success, stdout, stderr)
    """
    # Build compiler command
    cmd = ["build.bat", "RelWithDebInfo", "OpenSHC.dll"]
    
    try:
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            cwd=".",
            stdin=subprocess.DEVNULL,
        )
        return result.returncode == 0, result.stdout, result.stderr
    except Exception as e:
        return False, "", str(e)

@mcp.tool()
def extract_function_assembly_diff(function_name: str) -> tuple[bool, Any, str, str]:
    """
    Extract assembly diff for a specific function, comparing the original binary to the reimplementation source code. Should be called after writing and compiling a cpp file, see 'compile_cpp_code_for_function'.
    
    Args:
        function_name: Name of the function to extract, fully namespaced using '::'
    
    Returns:
        Tuple of (success, diff, stdout, stderr)
    """
    cmd = [str(Path("reccmp") / "run.bat"), "reccmp-reccmp", "--target", "STRONGHOLDCRUSADER", "--json", "diff.json"]
    
    try:
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            cwd=".",
            stdin=subprocess.DEVNULL,
        )
        if result.returncode != 0:
            raise Exception(f"could not create diff: {result.stderr}, command: {' '.join(cmd)}")
    except Exception as e:
        return False, "", "", f"could not execute reccmp/run: {str(e)}"
    try:
        diff = json.loads(Path("reccmp/diff.json").read_text())
    except Exception as e:
        return False, "", "", f"could not load reccmp/diff.json: {str(e)}"
    all_data = diff['data']
    data = [entry for entry in all_data if entry['name'] == function_name]
    if len(data) == 0:
        return False, "", "", f"no function with name '{function_name}' in diff.json"
    data = data[0]
    return True, data, "", ""

def function_name_to_cpp_path(function_name: str, base_path = Path("src")) -> tuple[bool, str, str]:
    parts = function_name.split("::")
    path = base_path
    for part in parts:
        if "." in part:
            return False, "", "illegal character in cpp file path: ."
        path = path / part
    return True, f"{str(path)}.cpp", ""

@mcp.tool()
def compile_cpp_code_for_function(function_name: str, contents: str) -> tuple[bool, str, str]:
    """
    Write and compile cpp code for function identified by fully namespaced function name.
    
    Args:
        function_name: Name of the function to extract, fully namespaced using '::'
        contents: New contents of the file
    
    Returns:
        Tuple of (success, stdout, stderr)
    """
    # Translate the function name into a path
    rstate, rresult, rerr = function_name_to_cpp_path(function_name=function_name)
    if not rstate:
        return rstate, "", f"could not resolve function name to file path: {rerr}"
    path = Path(rresult)
    if not path.exists():
        return False, "", f"cpp file path does not exist: {str(path)}"
    path.write_text(contents)

    # Ensure the cpp file is included in the build
    csentry = str(path).replace("\\", "/")
    if not csentry.startswith("src/"):
        return False, "", f"invalid cmake/openshc-sources.txt entry: {csentry}"
    
    lines = PATH_CMAKE_OPENSHC_SOURCES.read_text().splitlines(False)
    if not csentry in lines:
        lines.append(csentry)
    PATH_CMAKE_OPENSHC_SOURCES.write_text('\n'.join(lines))

    # Compile the project and return the resulting state
    return compile_project()

@mcp.tool()
def read_cpp_code_for_function(function_name: str) -> tuple[bool, str, str]:
    """
    Read the cpp code for a function
    
    Args:
        function_name: Name of the function to extract, fully namespaced using '::'
    
    Returns:
        Tuple of (success, contents, stderr)
    """
    rstate, rresult, rerr = function_name_to_cpp_path(function_name=function_name)
    if not rstate:
        return rstate, "", f"could not resolve function name to file path: {rerr}"
    path = Path(rresult)
    if not path.exists():
        return False, "", f"cpp file path does not exist: {str(path)}"
    try:
        return True, path.read_text(), ""
    except Exception as e:
        return False, "", f"{e}"

@mcp.tool()
def read_source_file(relative_path: str) -> tuple[bool, str, str]:
    """
    Read the C++ file contents of a file
    
    Args:
        relative_path: Name of the file, usually starts with 'OpenSHC/'
    
    Returns:
        Tuple of (success, contents, stderr)
    """
    src = Path("src")
    path = (src / Path(relative_path)).resolve()
    if not str(path).startswith(str(src.resolve())):
        return False, "", "Cannot escape src/ directory"
    if not path.exists():
        return False, "", f" cpp file path does not exist: {str(path)}"
    try:
        return True, path.read_text(), ""
    except Exception as e:
        return False, "", f"{e}"

@mcp.tool()
def fetch_ghidra_function_decompilation(function_name: str) -> tuple[bool, str, str]:
    """
    Fetches decompilation of a function (json with additional information). Contains ghidra special functions.
    
    Args:
        function_name: Name of the function to extract, fully namespaced using '::'
    
    Returns:
        Tuple of (success, contents, stderr)
    """
    try:
        resp = requests.get("http://127.0.0.1:11337/functions/decompile", params={
            "name": function_name,
        }, timeout=5)
        resp.raise_for_status()
        contents = resp.json()
        return True, json.dumps(contents), ""
    except Exception as e:
        return False, "", f"{e}"


if __name__ == "__main__":
    mcp.run(transport="stdio")
