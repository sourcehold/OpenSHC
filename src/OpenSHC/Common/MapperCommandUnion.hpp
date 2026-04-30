/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Common/MapperCommandUnion.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeShort.hpp"
#include "OpenSHC/SHDE/eMappersInt.hpp"
#include "OpenSHC/_SHCDE/eMappersInt.hpp"

namespace OpenSHC {
namespace Common {

    using OpenSHC::_SHCDE::eMappersInt;
    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Commands::CommandBuildingTypeShort;
    using OpenSHC::SHDE::eMappersInt;

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
