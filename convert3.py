from typing import Dict, List
from skink.architecture.enums import Enum, EnumResult
from skink.export.project.project import DatatypeDatabasePlan, DefineddataDatabasePlan, FunctionDatabasePlan, Project, SymbolsDatabasePlan
from skink.export.project.collection import ExportedContentCollection, ExportContents
from skink.architecture.structs.struct import Struct
from skink.architecture.unions.union import Union
from skink.architecture.functionsignatures import FunctionSignature
from skink.architecture.typedefs import Typedef
from skink.sarif.symbols.symbol import SymbolResult
from skink.sarif.datatypes.DataTypeResult import DataTypeResult
from skink.sarif.datatypes.FunctionSignatureResult import FunctionSignatureResult
from skink.sarif.datatypes.UnionResult import UnionResult
from skink.sarif.BasicResult import BasicResult
from skink.sarif.datatypes.TypedefResult import AdditionalTypedefProperties, Message, TypedefProperties, TypedefResult
import logging

from skink.export.classes.collect import collect_classes, collect_namespaced_functions
from skink.export.enums.enumfamilies import collect_enum_families
import pathlib
from skink.export.styles.style3.exporter import Exporter, BinaryContext, TransformationRules, FileRules

from skink.export.context import DEFAULT, Context
ctx: Context = DEFAULT.copy() # type: ignore
ctx.class_rules.suffix = ""
ctx.struct_rules.suffix = ""
ctx.include.file_extension = ""


import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--sarif", required=False, default="Stronghold Crusader.exe.sarif")
parser.add_argument("--clear-cache", required=False, action=argparse.BooleanOptionalAction, default=False)
parser.add_argument("--output-dir", required=False, default='src')
parser.add_argument("--verbose", default=False, action=argparse.BooleanOptionalAction)
parser.add_argument("--export-helpers", default=False, action=argparse.BooleanOptionalAction)
parser.add_argument("--overwrite-all", default=False, action=argparse.BooleanOptionalAction)
parser.add_argument("--export-cpp", default=False, action=argparse.BooleanOptionalAction)
parser.add_argument("--dry-run", default=False, action='store_true')
parser.add_argument("--cache", default=True, action=argparse.BooleanOptionalAction)
args = parser.parse_args()

if args.verbose:
  logging.getLogger().setLevel(logging.DEBUG)
  logging.getLogger().log(logging.DEBUG, args)

if args.dry_run:
  print(logging.getLogger().getEffectiveLevel())
  print(args)
  exit(0)

project = Project(args.sarif,
                  cache_objects=args.cache,
                  cache_path=".cache" if args.cache else None)

# TODO: permit_overwrite = False
logging.log(logging.INFO, "processing all symbol results")
project.build_database(plan_symbols=SymbolsDatabasePlan(store_symbol_result=True, permit_overwrite=True),
                       plan_datatype=DatatypeDatabasePlan(location_rewriter=lambda x: x.replace("_HoldStrong", "OpenSHC"),
                                                          filter=lambda x: x.properties.additionalProperties.location.startswith("/_HoldStrong")),
                       plan_defineddata=DefineddataDatabasePlan(),
                       plan_function=FunctionDatabasePlan(),
                       clear_cache=args.clear_cache)
#project.build_all_databases(log_progress=1000, store_symbol_result=True, permit_overwrite=True)
logging.log(logging.INFO, "processing all symbol results: finished")

# objs_i = 0
# for _ in project.yield_raw_objects():
#   objs_i += 1
#   print(objs_i)
import pickle
logging.log(logging.INFO, "finding all by location")
objs: List[BasicResult] = []
objs_i = 0
for obj in project.find_all_by_location(location="/_HoldStrong", recursive=True, lookup_lsymbols=True):
  if obj not in objs:
    objs_i += 1
    objs.append(obj)
logging.log(logging.INFO, "finding all by location: finished")


bc = BinaryContext(hash="3BB0A8C1", abbreviation="SHC", reccmp_binary="STRONGHOLDCRUSADER")
exporter = Exporter(binary_context=bc,
                    transformation_rules=TransformationRules(use_regex = True, regex={"_HoldStrong": "OpenSHC"}),
                    expose_original_methods=True,
                    file_rules = FileRules(one_file_per_function=True, one_file_per_method=True),
                    includes_remapping=[(".*DirectDraw/.*", "ddraw.h"),
                                        (".*/Mss32/.*", "Mss32.h"),
                                        (".*/binkw32/.*", "binkw32.h"),
                                        (".*inaddr.h", "WinSock.h"),
                                        (".*DirectPlay/dplay/.*", "dplay.h"),
                                        (".*DirectPlay/dplobby/.*", "dplobby.h"),
                                        # ("HoldStrong_lib/StringObject.*", "<string>"),
                                        ],
                    includes_exclude_regex=[".*Enums/WindowsVirtualKey.*",
                                            ".*Enums/GeneralWindowsMessage.*",
                                            ".*Enums/FilePtrMoveMethod/.*",
                                            ".*winapi_32/.*"],
                    exclude_files_regex=[
                      ".*Enums/WindowsVirtualKey.*",
                      ".*Enums/GeneralWindowsMessage.*",
                      ".*Enums/FilePtrMoveMethod/*",
                      ".*/Mss32/.*",
                      ".*/binkw32/.*",
                      ".*DirectDraw/.*",
                      ".*DirectPlay/dplay/.*",
                      ".*DirectPlay/dplobby/.*",
                    ],
                    type_mapping={
                      ("/_HoldStrong/WindowsHelper/Enums", "GeneralWindowsMessage"): ("/WinDef.h", "UINT"),
                      ("/_HoldStrong/WindowsHelper/Enums", "RawWindowsMessage"): ("/WinDef.h", "UINT"),
                      ("/_HoldStrong/WindowsHelper/Enums", "WindowsVirtualKey"): ("/WinDef.h", "WPARAM"),
                      ("/_HoldStrong/WindowsHelper/Enums", "GeneralWindowsMessageInt"): ("/WinDef.h", "UINT"),
                      ("/_HoldStrong/WindowsHelper/Enums", "RawWindowsMessageInt"): ("/WinDef.h", "UINT"),
                      ("/_HoldStrong/WindowsHelper/Enums", "WindowsVirtualKeyInt"): ("/WinDef.h", "WPARAM"),
                      ("/_HoldStrong/WindowsHelper/Enums", "FilePtrMoveMethod"): ("/stdio.h", "DWORD"),
                      ("/_HoldStrong/WindowsHelper/Enums", "FilePtrMoveMethodInt"): ("/stdio.h", "DWORD"),
                      ("/HoldStrong_lib", "StringObject"): ("/", "void *"),
                      ("/HoldStrong_lib", "StringObject *"): ("/", "void *"),
                    },
                    inject_forwards_in_files={
                      "OpenSHC/UI/Menu.hpp": [("OpenSHC/UI/FwdMenuMenuItem.hpp",
"""
namespace OpenSHC {
namespace UI {
    class Menu;
    class MenuItem;
}
}
""")],
                      "OpenSHC/UI/MenuItem.hpp": [("OpenSHC/UI/FwdMenuMenuItem.hpp",
"""
namespace OpenSHC {
namespace UI {
    class Menu;
    class MenuItem;
}
}
""")],
                    })

collection = ExportedContentCollection(ignore_duplicates=True)


logging.log(logging.INFO, "collecting classes")
clsses = list(collect_classes(objs))
logging.log(logging.INFO, "collecting classes: finished")

logging.log(logging.INFO, "collecting namespaced functions")
namespaced_functions = list(collect_namespaced_functions(objs))
logging.log(logging.INFO, "collecting namespaced functions: finished")

enum_families, enum_orphans = collect_enum_families(objs)
enum_families_dict = {f.name: f for f in enum_families}
enum_family_names = [f.name for f in enum_families]

def is_symbol_addr_in_useful_range(addr, include_code = True):
  if include_code:
    if addr >= 0x00401000 and addr < 0x0059e000:
      return True
  if addr == 0x00618250:
    return False
  if addr < 0x005a6e20:
    return False
  if addr >= 0x005a6f00 and addr < 0x005b6004:
    return False
  if addr >= 0x00b93208 and addr < 0x00b94220:
    return False
  if addr >= 0x00b94228 and addr < 0x00b95780:
    return False
  if addr >= 0x00b383f0 and addr < 0x00b3868c:
    return False
  if addr >= 0x02427478:
    return False
  return True

from skink.export.mangler import build_extern_symbol

## raise Exception()
# # DEBUGGING
# asm_declarations = []
# asm_addresses = []
# for addr, symb, ddr, dt, isClass in project.find_global_primary_symbol_defined_data_pairs_by_address():
#   primitive = True
#   prop = ddr.properties.additionalProperties
#   if prop.typeLocation == "/_HoldStrong":
#     primitive = False
#     ns = project.loc_name_to_parts(prop.typeLocation, prop.typeName)

def typedefFunc(loc: str, name: str, prefix: str):
  if loc.startswith("/OpenSHC/"):
    if name.endswith("Int"):
      return "/", "int", ""
    if name.endswith("Short"):
      return "/", "short", ""
    if name.endswith("Byte"):
      return "/", "byte", ""
    if name.startswith("IDirectPlay4A"):
      return "/", name.replace("IDirectPlay4A", "IDirectPlay4"), "struct "

  return loc, name, prefix

asm = exporter.export_symbols_as_assembly(((addr, symb, ddr, dt, isClass) for addr, symb, ddr, dt, isClass in project.find_global_primary_symbol_defined_data_pairs_by_address() if is_symbol_addr_in_useful_range(addr, include_code=False)),
      destination="symbols/data.asm", 
      typedefs={
        ('/OpenSHC/WindowsHelper/Enums', 'BOOLEnum'): ('/', 'int', ""),
        ('/winnt', 'LARGE_INTEGER'): ('/', '_LARGE_INTEGER', "union "),
        ('/OpenSHC/DirectPlay/dplay', 'IDirectPlay4A'): ("/", "IDirectPlay4", "struct "),
      },
      typedef_func=typedefFunc)
collection.add(asm)

collection.write_to_disk(pathlib.Path(args.output_dir), overwrite_all=args.overwrite_all, no_touch_warning="THIS FILE IS AUTO GENERATED\n  Communicate changes to the dev team (e.g. via a Pull Request).\n  Changes get lost otherwise.")

for c in exporter.export_symbols(((addr, symb, ddr,) for addr, symb, ddr, dt, isClass in project.find_global_primary_symbol_defined_data_pairs_by_address() if is_symbol_addr_in_useful_range(addr, include_code=False)), destination="OpenSHC/Globals", namespace="OpenSHC"):
  collection.add(c)

if args.export_helpers:
  collection.add(*exporter.export_helpers())

for cls in clsses:
  collection.add(*exporter.export_class(cls, export_bodies=args.export_cpp))
for ns in namespaced_functions:
  reimplementation_unifier = None
  if ns.name == "OS":
    reimplementation_unifier = "REIMPLEMENTED_CRT"
  collection.add(*exporter.export_namespace(ns, export_bodies=args.export_cpp, reimplementation_unifier=reimplementation_unifier))

collection.add(exporter.export_addresses(project.yield_raw_objects()))

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
    if e.name == "BOOLEnum":
      # Swallow Ghidras enum
      collection.add(exporter.export_typedef_raw(location="OpenSHC/WindowsHelper/Enums",
                                                 namespace_path="OpenSHC::WindowsHelper::Enums",
                                                 name="BOOLEnum",
                                                 type="BOOL"))
    elif obj in enum_orphans:
      #if e.er.properties.additionalProperties.size == 4:
      collection.add(exporter.export_enum(e))
      #else:
      #  collection.add(*exporter.export_sized_enum(e))
    else:
      if obj.properties.additionalProperties.name in enum_family_names:
        # is root
        if obj.properties.additionalProperties.size != 4:
          logging.warning(f"root enum of family is not of type int: '{e.location(ctx)}/{e.name}'")
        collection.add(exporter.export_enum(e))
      else:
        # TODO: add "startswith" logic to find the actual family?
        collection.add(exporter.export_enum_typedef(e))
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

def write_patches(output_dir: pathlib.Path):
  patch1 = """/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MSS/UnkSoundFlagsAndLoopCount.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Audio {
    namespace MSS {

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef struct UnkSoundFlagsAndLoopCount {

            unsigned int loopCount : 16;
            int reserved : 13;
            int unknownFlag1 : 1;
            int unknownFlag2 : 1;
            int uninterruptable : 1;

        } UnkSoundFlagsAndLoopCount;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnkSoundFlagsAndLoopCount) == 4, UnkSoundFlagsAndLoopCount);
    } // namespace MSS
} // namespace Audio
} // namespace OpenSHC
"""
  (output_dir / "OpenSHC/Audio/MSS/UnkSoundFlagsAndLoopCount.hpp").write_bytes(patch1.encode('utf-8'))

if not args.dry_run:
  # TODO: 
  collection.write_to_disk(pathlib.Path(args.output_dir), overwrite_all=args.overwrite_all, no_touch_warning="THIS FILE IS AUTO GENERATED\n  Communicate changes to the dev team (e.g. via a Pull Request).\n  Changes get lost otherwise.")
  write_patches(pathlib.Path(args.output_dir))