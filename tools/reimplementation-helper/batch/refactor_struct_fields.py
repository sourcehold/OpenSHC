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

field_offset_extractor_re_factory = lambda field_name: re.compile(f"{field_name}(?:\\[[^; ]+)*; // 0x([0-9A-Za-z]+) length: [0-9]+")

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

database: Dict[LookupQuery, str] = {}

@dataclass(frozen=True)
class Error2039Line:
  occurrence_path: str
  occurrence_line: int
  missing_field: str
  target_structure: str
  target_path: str
  new_field_name: str

  def solve(self, dry_run = False):
    noop = True
    content = pathlib.Path(self.occurrence_path).read_text(newline="\n").splitlines(keepends=True)
    needles = [f"->{self.missing_field}", f".{self.missing_field}"]
    needles_new = [f"->{self.new_field_name}", f".{self.new_field_name}"]
    for offset in (0, -1, 1):
      index = offset + self.occurrence_line - 1
      line = content[index]
      detections = [needle in line for needle in needles]
      if not any(detections):
        detections_new = [needle in line for needle in needles_new]
        if any(detections_new):
          noop = False
          logging.warning(f"did not find faulty field ({self.missing_field}) but did find new field ({self.new_field_name}), skipping this entry in {self.occurrence_path} line {index+1}")
        continue
      content[index] = line.replace(self.missing_field, self.new_field_name)
      noop = False
    if noop:
      raise Exception(f"did not find faulty field {self.missing_field} nor new field {self.new_field_name} in {self.occurrence_path} line {self.occurrence_line}\n\t{line}")
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
    lookupresult = database[query]
    return Error2039Line(occurrence_path=occurrence_path, occurrence_line=occurrence_line, target_structure=target_structure, missing_field=missing_field, new_field_name=lookupresult, target_path=target_structure_path)
  
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
  database[query] = new_field_name
  return Error2039Line(occurrence_path=occurrence_path, occurrence_line=occurrence_line, target_structure=target_structure, missing_field=missing_field, new_field_name=new_field_name, target_path=target_structure_path)

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
  args = parser.parse_args()
  if args.verbose:
    logging.getLogger().setLevel(logging.DEBUG)
  path = args.error_log
  lines = pathlib.Path(path).read_text().splitlines()
  solutions_raw: List[None | Error2039Line] = [parse_missing_field_line(line) for line in lines]
  solutions: List[Error2039Line] = [sol for sol in solutions_raw if sol]
  for sol in solutions:
    sol.solve(dry_run=args.dry_run)
