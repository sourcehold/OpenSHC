import pyghidra

if not pyghidra.started():
  pyghidra.start()

import atexit
import tempfile
import pyghidra

from ghidra.base.project import GhidraProject
from ghidra.app.util.importer import ProgramLoader
from ghidra.util.task import ConsoleTaskMonitor
from ghidra.program.flatapi import FlatProgramAPI


import sarif.export.SarifExporter
import java.io.File
import sarif.SarifProgramOptions

def initialize_ghidra_from_gzf(gzfPath: str = "Stronghold Crusader.exe.gzf"):
  project_dir = tempfile.mkdtemp(prefix="ghidra-project-")
  project_name = "temp-project"

  global project
  project = pyghidra.open_project(project_dir, project_name, True)
  loader = pyghidra.program_loader().project(project)
  #fh = File(gzfPath, "rb")
  loader = loader.source(gzfPath)
  with loader.load() as load_results:
    load_results.save(pyghidra.task_monitor()) # type: ignore
  
  global currentProgram
  currentProgram, obj = pyghidra.consume_program(project, "/Stronghold Crusader.exe", project)

  global flat_api
  flat_api = FlatProgramAPI(currentProgram, pyghidra.task_monitor())

import argparse
parser = argparse.ArgumentParser()

parser.add_argument("--sarif", default="Stronghold Crusader.exe.sarif")
parser.add_argument("--gzf", default="Stronghold Crusader.exe.gzf")

if __name__ == "__main__":
    args = parser.parse_args()

    initialize_ghidra_from_gzf(args.gzf)

    opts = sarif.SarifProgramOptions()
    opts.setInstructions(False)
    opts.setMemoryContents(False)

    e = sarif.export.SarifExporter()
    assert e.export(java.io.File(args.sarif), currentProgram, None, pyghidra.task_monitor())