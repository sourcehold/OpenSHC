import logging

from dataclasses import dataclass

import pathlib
import re
import os, subprocess
from typing import Dict, List

occurrence_re = re.compile("^([A-Za-z0-9_/\\\\]+[.]cpp)[(]([0-9]+)[)]")

new_field_name_re_factory = lambda offset: re.compile(f"([A-Za-z0-9_]+)(\\[[^; ]+)*; // 0x{offset:08X} length: [0-9]+")

missing_field_re = re.compile(".* error C2039: '([^' ]+)'")

quick_field_re = re.compile("field[0-9A-Za-z]+_0x([0-9A-Za-z]+)")

target_structure_re = re.compile(".*is not a member of '([^' ]+)'")

cast_before_field_re = lambda field_name: re.compile(f"[*][(][^)]*[*][)][^;]*[.>]{field_name}")

field_offset_extractor_re_factory = lambda field_name: re.compile(f"{field_name}(?:\\[[^; ]+)*; // 0x([0-9A-Za-z]+) length: [0-9]+")

# How far from the line cl reports to look for the field name; see Error2039Line.solve.
WINDOW = 6


def offsets(window):
  """0, -1, +1, -2, +2, ... up to +-window: nearest the reported line first."""
  yield 0
  for distance in range(1, window + 1):
    yield -distance
    yield distance


directory_variants = {"src/OpenSHC/Audio/MSS/": "src/OpenSHC/Audio/mss/"}
directory_variants_alternative = {}
for key, value in directory_variants.items():
  directory_variants_alternative[value] = key
directory_variants.update(directory_variants_alternative)

@dataclass(frozen=True)
class LookupQuery:
  missing_field: str
  target_structure: str
  target_path: str  

database: Dict[LookupQuery, tuple] = {}  # query -> (new name, is array)

@dataclass(frozen=True)
class Error2039Line:
  occurrence_path: str
  occurrence_line: int
  missing_field: str
  target_structure: str
  target_path: str
  new_field_name: str
  new_field_is_array: bool = True

  def solve(self, dry_run = False, window = WINDOW):
    # cl reports a field at the line the *statement* ends on, which for a call argument
    # wrapped by clang-format is several lines below the line that names the field. A
    # window of the reported line and its two neighbours left those behind
    # (processHelpRichTextTokens: reported at 355, named at 353), so scan further, and
    # nearest-first so a name occurring twice is taken from the line cl pointed at.
    replaced = 0
    found_new = False
    content = pathlib.Path(self.occurrence_path).read_text(newline="\n").splitlines(keepends=True)
    needles = [f"->{self.missing_field}", f".{self.missing_field}"]
    needles_new = [f"->{self.new_field_name}", f".{self.new_field_name}"]
    for offset in offsets(window):
      index = offset + self.occurrence_line - 1
      if not 0 <= index < len(content):
        continue
      line = content[index]
      if not any(needle in line for needle in needles):
        found_new = found_new or any(needle in line for needle in needles_new)
        continue
      content[index] = line.replace(self.missing_field, self.new_field_name)
      replaced += 1
      if not self.new_field_is_array and cast_before_field_re(self.missing_field).search(line):
        # A Ghidra sync that turns undefined1 padding_0xNN[2] into short field_0xNN also
        # invalidates the `*(short*)field` the old array needed: renaming alone leaves a
        # cast of the field's *value* to a pointer, which compiles and stores nowhere
        # near the field (SetHovelBuildOrder, 0x286). Assign the field directly instead.
        logging.warning(f"{self.occurrence_path} line {index+1}: {self.new_field_name} is no longer an array but the line still casts it - drop the cast by hand:\n\t{line.strip()}")
    if replaced == 0:
      if found_new:
        # An earlier entry of this run already renamed it: cl reports the field once per
        # line, so one rename can answer several error lines.
        logging.debug(f"already renamed to {self.new_field_name} near {self.occurrence_path} line {self.occurrence_line}")
        return
      raise Exception(f"did not find faulty field {self.missing_field} nor new field {self.new_field_name} in {self.occurrence_path} line {self.occurrence_line} (window +-{window})")
    if not dry_run:
      pathlib.Path(self.occurrence_path).write_text("".join(content), newline="")

def parse_missing_field_line(line: str):
  if not " error C2039: " in line or " namespace" in line:
    return None
  m = occurrence_re.match(line)
  if not m:
    if ".hpp" in line:
      return None
    raise Exception(f"cannot find occurrence path: {line}")
  occurrence_line = int(m.group(2)) # type: ignore
  occurrence_path = "src/OpenSHC/" + m.group(1).replace("\\", "/") # type: ignore
  if not pathlib.Path(occurrence_path).exists():
    raise Exception(f"file not found: {occurrence_path}")
  m = missing_field_re.match(line)
  if not m:
    raise Exception(f"cannot find missing field: {line}")
  missing_field: str = m.group(1) # type: ignore
  m = target_structure_re.match(line)
  if not m:
    raise Exception(f"could not find target structure: {line}")
  target_structure :str = m.group(1) # type: ignore
  target_structure_path = "src/" + target_structure.replace("::", "/") + ".hpp"
  if not pathlib.Path(target_structure_path).exists():
    raise Exception(f"target structure does not exist on disk: {target_structure_path}")
  query = LookupQuery(missing_field=missing_field, target_structure=target_structure, target_path=target_structure_path)
  if query in database:
    lookupresult, is_array = database[query]
    return Error2039Line(occurrence_path=occurrence_path, occurrence_line=occurrence_line, target_structure=target_structure, missing_field=missing_field, new_field_name=lookupresult, target_path=target_structure_path, new_field_is_array=is_array)
  
  quick_field = quick_field_re.match(missing_field)
  offset = None
  if not quick_field:
    parts = target_structure_path.split("/")
    base_path = "/".join(parts[:-1] + [""])
    if base_path in directory_variants:
      target_structure_path_variant = f"{directory_variants[base_path]}{parts[-1]}"
      try:
        offset = git_lookup_old_field_offset(missing_field, target_structure_path)
      except Exception as e:
        logging.debug(e)
        offset = git_lookup_old_field_offset(missing_field, target_structure_path_variant)
    else:
      offset = git_lookup_old_field_offset(missing_field, target_structure_path)
  else:
    offset = int(quick_field.group(1), 16)
  if offset is None:
    raise Exception(f"offset not found: {line}")
  text = pathlib.Path(target_structure_path).read_text()
  matches = new_field_name_re_factory(offset).findall(text)
  if len(matches) == 0:
    raise Exception(f"could not find the new field: {line} {offset:08X}")
  if len(matches) > 1:
    raise Exception(f"found multiple new fields: {line} {offset:08X}")
  new_field_name = matches[0][0]
  new_field_is_array = bool(matches[0][1])
  database[query] = (new_field_name, new_field_is_array)
  return Error2039Line(occurrence_path=occurrence_path, occurrence_line=occurrence_line, target_structure=target_structure, missing_field=missing_field, new_field_name=new_field_name, target_path=target_structure_path, new_field_is_array=new_field_is_array)

def git_lookup_old_field_offset(field_name: str, path: str):
  args = ["git", "rev-list", "--all", "--", path]
  logging.debug(" ".join(args))
  status, output = subprocess.getstatusoutput(args)
  if status != 0:
    raise Exception("failed to execute git rev list for path: {path}")
  outputs = [o for o in output.split("\n") if o]
  for o in outputs:
    args = ["git", "grep", field_name, o, "--", path]
    logging.debug(" ".join(args))
    status, result = subprocess.getstatusoutput(args)
    if status == 0:
      hits = field_offset_extractor_re_factory(field_name=field_name).findall(result)
      if len(hits) != 1:
        raise Exception(f"{field_name} {path} {hits}")
      return int(hits[0], 16)
  raise Exception(f"could not find offset: {field_name} {path}")

def test():
  print(parse_missing_field_line(r"# UI\Credits\AppendCreditsPauseCommand.cpp(14) : error C2039: 'field0_0x0' : is not a member of 'OpenSHC::UI::Credits::CreditsRelatedStructure2'"))

if __name__ == "__main__":
  import sys

  import argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("error_log", help="path to the error log file from syntax_check.py")
  parser.add_argument("--dry-run", help="Set whether to do a dry run or modify cpp files", action="store_true", default=False, required=False)
  parser.add_argument("--verbose", help="Set verbosity to DEBUG", action="store_true", default=False, required=False)
  parser.add_argument("--window", help=f"lines either side of the reported one to search (default {WINDOW})", type=int, default=WINDOW, required=False)
  args = parser.parse_args()
  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)
  path = args.error_log
  lines = pathlib.Path(path).read_text().splitlines()
  solutions_raw: List[None | Error2039Line] = [parse_missing_field_line(line) for line in lines]
  solutions: List[Error2039Line] = [sol for sol in solutions_raw if sol]
  for sol in solutions:
    sol.solve(dry_run=args.dry_run, window=args.window)
