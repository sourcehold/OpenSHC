#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Enums::HSM_NONE;
    using OpenSHC::Map::Enums::HSM_STONE;
    using OpenSHC::Map::Enums::HSM_WOOD;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8210
    OpenSHC::Map::Enums::HitSoundMaterialInt TileMapState::getBuildingHurtSFXID(int tile)
    {
        short buildingID = this->BuildingLayer[tile];
        if (buildingID != 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == 0) {
                return HSM_NONE;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                == OpenSHC::Map::Buildings::BLS_REMOVE) {
                return HSM_NONE;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].currentHealth == 0) {
                return HSM_NONE;
            }

            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_BARRACKS:
            case OpenSHC::Map::Buildings::BT_STOCKPILE:
            case OpenSHC::Map::Buildings::BT_ARMORY:
            case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
            case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
            case OpenSHC::Map::Buildings::BT_CHAPEL:
            case OpenSHC::Map::Buildings::BT_CHURCH:
            case OpenSHC::Map::Buildings::BT_CATHEDRAL:
            case OpenSHC::Map::Buildings::BT_MANORHOUSE:
            case OpenSHC::Map::Buildings::BT_STONEKEEP:
            case OpenSHC::Map::Buildings::BT_STRONGHOLD:
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            case OpenSHC::Map::Buildings::BT_GATEHOUSE:
            case OpenSHC::Map::Buildings::BT_TOWER1:
            case OpenSHC::Map::Buildings::BT_TOWER2:
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
            case OpenSHC::Map::Buildings::BT_TOWER5:
            case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
                return HSM_STONE;
            default:
                return HSM_WOOD;
            }
        }
        if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
            return HSM_STONE;
        }
        return HSM_NONE;
    }

}
}
