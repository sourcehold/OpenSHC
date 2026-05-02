/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Common/MapperCommandUnion.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeShort.hpp"
#include "OpenSHC/DE/SHCDE/eMappersInt.hpp"
#include "OpenSHC/DE/SHDE/eMappersInt.hpp"

namespace OpenSHC {
namespace Common {

    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Commands::CommandBuildingTypeShort;
    using OpenSHC::DE::SHCDE::eMappersInt;
    using OpenSHC::DE::SHDE::eMappersInt;

#pragma pack(push, 1)
    // SIZE: 0x00000004
    typedef union MapperCommandUnion {

        eMappersInt sh1; // 0x00000000 length: 4
        CommandBuildingTypeInt shc; // 0x00000000 length: 4
        CommandBuildingTypeShort shcShort; // 0x00000000 length: 2
        eMappersInt shcde; // 0x00000000 length: 4

    } MapperCommandUnion;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MapperCommandUnion) == 4, MapperCommandUnion);
} // namespace Common
} // namespace OpenSHC
