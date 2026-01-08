#!/usr/bin/env python3
"""
MCP Server for C++ decompilation and assembly comparison tasks.

This server provides tools for:
- Compiling C++ files with MSVC
- Comparing assembly output with target assembly
- Generating assembly diffs

Usage:
    python decomp_mcp_server.py

Environment variables:
    MSVC_PATH: Path to MSVC compiler (cl.exe directory)
    PROJECT_ROOT: Root directory of the project
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
sys.stdout.reconfigure(line_buffering=True)
sys.stderr.reconfigure(line_buffering=True)
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


# Initialize MCP server
mcp = FastMCP("decomp-helper")

def compile_project() -> tuple[bool, str, str]:
    """
    Compile the C++ project using MSVC. Must be executed after writing new cpp file contents.
    
    Returns:
        Tuple of (success, stdout, stderr)
    """
    # Build compiler command
    cmd = ["build.bat", "build", "RelWithDebInfo"]
    
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
    parts = function_name.split("::")
    src = Path("src")
    path = src
    for part in parts:
        if "." in part:
            return False, "", "illegal character in cpp file path: ."
        path = path / part
    path = Path(f"{str(path)}.cpp")
    if not path.exists():
        return False, "", f" cpp file path does not exist: {str(path)}"
    path.write_text(contents)
    
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
    parts = function_name.split("::")
    src = Path("src")
    path = src
    for part in parts:
        if "." in part:
            return False, "", "illegal character in cpp file path: ."
        path = path / part
    path = Path(f"{str(path)}.cpp")
    if not path.exists():
        return False, "", f" cpp file path does not exist: {str(path)}"
    try:
        return True, path.read_text(), ""
    except Exception as e:
        return False, "", f"{e}"

import sys

if __name__ == "__main__":
    mcp.run(transport="stdio")
