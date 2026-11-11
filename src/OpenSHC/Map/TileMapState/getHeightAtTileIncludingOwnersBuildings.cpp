#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FFF10
    uint TileMapState::getHeightAtTileIncludingOwnersBuildings(int tile, int playerID)
    {
        // The early layer reads go through the global instance's absolute address, while the
        // BuildingLayer reads inside the switch arms go through this; follow each one separately.
        if (DAT_TileMapState::instance.PathConnectionLayer[tile] == 0) {
            return 0;
        }
        if ((DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0x1000) != 0) {
            return 0;
        }

        if ((DAT_TileMapState::instance.LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
            if (playerID != 0 && (this->WallOwnerLayer[tile] & 7) + 1 != playerID) {
                return 0;
            }
            return DAT_TileMapState::instance.HeightLayer[tile];
        }

        if (DAT_TileMapState::instance.BuildingLayer[tile] == 0) {
            return 0;
        }
        int const building = DAT_TileMapState::instance.BuildingLayer[tile];
        if (playerID != 0 && DAT_BuildingsState::instance.buildings[building].owner != playerID) {
            return 0;
        }

        switch (DAT_BuildingsState::instance.buildings[building].buildingType) {
        case OpenSHC::Map::Buildings::BT_STONEKEEP:
        case OpenSHC::Map::Buildings::BT_STRONGHOLD:
        case OpenSHC::Map::Buildings::BT_KEEPFOUR:
        case OpenSHC::Map::Buildings::BT_KEEPFIVE:
        case OpenSHC::Map::Buildings::BT_TOWER1:
        case OpenSHC::Map::Buildings::BT_TOWER2:
        case OpenSHC::Map::Buildings::BT_TOWER3:
        case OpenSHC::Map::Buildings::BT_TOWER4:
        case OpenSHC::Map::Buildings::BT_TOWER5:
            for (int direction = 0; direction < 8; direction++) {
                if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[DAT_ViewportRenderState::
                                                instance.tileTranslationMatrix_YComponent[tile]][direction]
                        + tile]
                    != building) {
                    return 0;
                }
            }
            break;
        case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
        case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL: {
            int firstDirection;
            int secondDirection;
            if (DAT_BuildingsState::instance.buildings[building].buildingVariation == 80) {
                firstDirection = 2;
                secondDirection = 6;
            } else {
                firstDirection = 0;
                secondDirection = 4;
            }
            int const tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[tileY][firstDirection] + tile]
                != building) {
                return 0;
            }
            if (this->BuildingLayer[DAT_TileMapState::instance.directionTranslationMatrix[tileY][secondDirection]
                    + tile]
                != building) {
                return 0;
            }
            break;
        }
        default:
            return 0;
        }
        return MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, this)(tile);
    }

}
}
