/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Common/MapperCommandUnion.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeShort.hpp"
#include "OpenSHC/DE/SHCDE/eMappersSHCDEInt.hpp"
#include "OpenSHC/DE/SHDE/eMappersSHDEInt.hpp"

namespace OpenSHC {
namespace Common {

    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Commands::CommandBuildingTypeShort;
    using OpenSHC::DE::SHCDE::eMappersSHCDEInt;
    using OpenSHC::DE::SHDE::eMappersSHDEInt;

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union MapperCommandUnion {

        eMappersSHDEInt sh1; // 0x00000000 length: 4
        CommandBuildingTypeInt shc; // 0x00000000 length: 4
        CommandBuildingTypeShort shcShort; // 0x00000000 length: 2
        eMappersSHCDEInt shcde; // 0x00000000 length: 4

    } MapperCommandUnion;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MapperCommandUnion) == 4, MapperCommandUnion);
} // namespace Common
} // namespace OpenSHC
