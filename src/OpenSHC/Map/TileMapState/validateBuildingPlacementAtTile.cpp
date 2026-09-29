#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F9DF0
    void TileMapState::validateBuildingPlacementAtTile(int playerID, int x, int y)
    {
        this->buildingPlacementFail = FALSE;
        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        int buildingID = this->BuildingLayer[tile];
        if (buildingID < 1 || (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID && playerID != 0)) {
            this->buildingPlacementFail = TRUE;
        }
        if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0 && this->BuildingLayer[tile] == 0) {
            if ((this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                return;
            }
            this->buildingPlacementFail = FALSE;
        }
        if ((this->LogicLayer[tile] & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_GATEHOUSESMALL
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_WOODGATE1
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_WOODGATE2
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_KEEPDOOR
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_DRAWBRIDGE
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_CAMPGROUND
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_PARADEGROUND
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_PARADEGROUND2
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_PARADEGROUND3
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_PARADEGROUND4
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_PARADEGROUND5
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_CAMPFIRE
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType
                != OpenSHC::Map::Buildings::BT_KILLINGPIT) {
            this->buildingPlacementFail = TRUE;
        }
        this->field131_0x554954 = buildingID;
    }

}
}
