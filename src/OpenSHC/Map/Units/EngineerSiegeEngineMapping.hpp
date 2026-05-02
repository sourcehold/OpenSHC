/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/EngineerSiegeEngineMapping.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::CommandBuildingTypeInt;
        using OpenSHC::Map::Buildings::BuildingTypeInt;
        using OpenSHC::Map::Units::UnitTypeInt;

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct EngineerSiegeEngineMapping {

            int slot; // 0x00000000 length: 4
            UnitTypeInt unitType; // 0x00000004 length: 4
            BuildingTypeInt buildingType; // 0x00000008 length: 4
            CommandBuildingTypeInt commandBuildingType; // 0x0000000C length: 4

        } EngineerSiegeEngineMapping;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(EngineerSiegeEngineMapping) == 16, EngineerSiegeEngineMapping);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
