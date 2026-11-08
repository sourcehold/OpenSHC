#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E410
        BOOLEnum BuildingsState::findFreeTunnelerAssemblyTile(int playerID, int unitID)
        {
            int const index = (int)DAT_GameState::instance.playerDataArray[playerID].someCount29;
            if (DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[2].x != 0) {
                int const assemblyX
                    = DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[2].x;
                int const assemblyY
                    = DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[2].y;
                for (int i = index; i < 49; ++i) {
                    int const x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].x + assemblyX;
                    int const y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].y + assemblyY;
                    int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    int const occupantID = (short)DAT_TileMapState::instance.UnitLayer[tile];
                    if (occupantID != 0 && occupantID != unitID
                        && DAT_UnitsState::instance.units[unitID].movementRelated == 8) {
                        continue;
                    }
                    if (MACRO_CALL_MEMBER(
                            Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(playerID,
                            (short)DAT_TileMapState::instance
                                .PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile],
                            (short)DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                        != 0) {
                        this->DAT_TempXOffset = x;
                        this->DAT_TempYOffset = y;
                        if (x == DAT_UnitsState::instance.units[unitID].x
                            && y == DAT_UnitsState::instance.units[unitID].y) {
                            return FALSE;
                        }
                        return TRUE;
                    }
                }
                return FALSE;
            }
            for (int i = index; i < 25; ++i) {
                int const x
                    = DAT_GameState::instance.playerDataArray[playerID].tunnelersGuildParadegroundLocations[i].x;
                int const y
                    = DAT_GameState::instance.playerDataArray[playerID].tunnelersGuildParadegroundLocations[i].y;
                if ((uint)x > OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1 || (uint)y > OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * OpenSHC::Map::MC_MAP_XY_LIMIT + x]
                        == 0) {
                    continue;
                }
                int const occupantID
                    = (short)DAT_TileMapState::instance
                          .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                if (occupantID != 0 && occupantID != unitID
                    && DAT_UnitsState::instance.units[unitID].movementRelated == 8) {
                    continue;
                }
                this->DAT_TempXOffset = x;
                this->DAT_TempYOffset = y;
                if (x == DAT_UnitsState::instance.units[unitID].x && y == DAT_UnitsState::instance.units[unitID].y) {
                    return FALSE;
                }
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
