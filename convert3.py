from typing import List
from skink.architecture.enums import Enum, EnumResult
from skink.export.project.project import Project
from skink.export.project.collection import ExportedContentCollection, ExportContents
from skink.architecture.structs.struct import Struct
from skink.architecture.unions.union import Union
from skink.architecture.functionsignatures import FunctionSignature
from skink.architecture.typedefs import Typedef
from skink.sarif.datatypes.DataTypeResult import DataTypeResult
from skink.sarif.datatypes.FunctionSignatureResult import FunctionSignatureResult
from skink.sarif.datatypes.UnionResult import UnionResult
from skink.sarif.BasicResult import BasicResult
from skink.sarif.datatypes.TypedefResult import TypedefResult
import logging
logging.getLogger().setLevel(logging.DEBUG)
from skink.export.classes.collect import collect_classes, collect_namespaced_functions
import pathlib
from skink.export.styles.style3.exporter import Exporter, BinaryContext, TransformationRules, FileRules

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--sarif", required=False, default="Stronghold Crusader.exe.all.sarif")
parser.add_argument("--clear-cache", required=False, action='store_true', default=False)
args = parser.parse_args()

if args.clear_cache:
  pathlib.Path(".cached-symbols.bin").unlink()
  pathlib.Path(".cached-objs.bin").unlink()

project = Project(args.sarif, cache_objects=True, cache_symbols_to_path=".cached-symbols.bin")

# TODO: permit_overwrite = False
logging.log(logging.INFO, "processing all symbol results")
project.process_all_symbol_results(log_progress=1000, store_symbol_result=True, permit_overwrite=True)
logging.log(logging.INFO, "processing all symbol results: finished")

# objs_i = 0
# for _ in project.yield_raw_objects():
#   objs_i += 1
#   print(objs_i)
import pickle
if pathlib.Path(".cached-objs.bin").exists() == False:
  logging.log(logging.INFO, "finding all by location")
  objs: List[BasicResult] = []
  objs_i = 0
  for obj in project.find_all_by_location(location="/_HoldStrong", recursive=True, lookup_lsymbols=True):
    objs_i += 1
    print(f"{objs_i}\t\t{obj.ruleId}")
    objs.append(obj)
  logging.log(logging.INFO, "finding all by location: finished")
  with open(".cached-objs.bin", 'wb') as f:
    pickle.dump(file=f, obj=objs)
else:
  with open(".cached-objs.bin", 'rb') as f:
    objs = pickle.load(file=f)

logging.log(logging.INFO, "collecting classes")
clsses = list(collect_classes(objs))
logging.log(logging.INFO, "collecting classes: finished")

logging.log(logging.INFO, "collecting namespaced functions")
namespaced_functions = list(collect_namespaced_functions(objs))
logging.log(logging.INFO, "collecting namespaced functions: finished")

bc = BinaryContext(hash="3BB0A8C1", abbreviation="SHC", reccmp_binary="STRONGHOLDCRUSADER")
exporter = Exporter(binary_context=bc, transformation_rules=TransformationRules(use_regex = True, regex={"_HoldStrong": "OpenSHC"}), expose_original_methods=True,
                    file_rules = FileRules(one_file_per_function=True, one_file_per_method=True))

collection = ExportedContentCollection(ignore_duplicates=True)

collection.add(*exporter.export_helpers())

for cls in clsses:
  collection.add(*exporter.export_class(cls))

for ns in namespaced_functions:
  collection.add(*exporter.export_namespace(ns))

collection.add(exporter.export_addresses(project.yield_objects()))

from skink.export.context import DEFAULT, Context
ctx: Context = DEFAULT.copy() # type: ignore
ctx.class_rules.suffix = ""
ctx.struct_rules.suffix = ""
ctx.include.file_extension = ""

class_paths = set(cls.location(ctx) for cls in clsses)

for obj in objs:
  if isinstance(obj, DataTypeResult):
    if obj.message.text == "DT.Struct":
      global S
      s = Struct(obj)
      if s.name == "GameSynchronyState":
        S = s
      if s.path(ctx) not in class_paths:
        collection.add(exporter.export_struct(s))
  elif isinstance(obj, EnumResult):
    e = Enum(obj)
    if e.er.properties.additionalProperties.size == 4:
      collection.add(exporter.export_enum(e))
    else:
      collection.add(*exporter.export_sized_enum(e))
  elif isinstance(obj, UnionResult):
    e = Union(obj)
    collection.add(exporter.export_union(e))
  elif isinstance(obj, FunctionSignatureResult):
    fsr = FunctionSignature(obj)
    collection.add(exporter.export_function_signature(fsr))
  elif isinstance(obj, TypedefResult):
    td = Typedef(obj)
    if "*" in td.name:
      continue
    collection.add(exporter.export_typedef(td))

collection.write_to_disk(pathlib.Path("src/"), overwrite_all=True)
