#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_DAIRY;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT;

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8160
    int TileMapState::getNonFarmFieldBuildingHealthAtTileOr1000(int tile)
    {
        short buildingID = this->BuildingLayer[tile];
        if (buildingID <= 0) {
            return 1000;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == 0) {
            return 1000;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == OpenSHC::Map::Buildings::BLS_REMOVE) {
            return 1000;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].currentHealth == 0) {
            return 1000;
        }
        if (DAT_BuildingDefinedData::instance
                .BuildingTypeHasHealth[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
            == 0) {
            return 1000;
        }

        if ((this->LogicLayer[tile] & (L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY))
            != 0) {
            return 1000;
        }
        return DAT_BuildingsState::instance.buildings[buildingID].currentHealth;
    }

}
}
