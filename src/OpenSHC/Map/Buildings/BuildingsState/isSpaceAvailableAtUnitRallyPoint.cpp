#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D6E0
        BOOLEnum BuildingsState::isSpaceAvailableAtUnitRallyPoint(int playerID, int group, int unitID)
        {
            int const requestedGroup = group;
            if (DAT_GameSynchronyState::instance.currentGameMode != 0
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0
                && DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2) {
                int const keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
                if (keepID == 0) {
                    return FALSE;
                }
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[keepID].someX;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[keepID].someY;
                return TRUE;
            }
            if (group == 6) {
                group = 5;
            }
            int offset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffsetsUnk[group];
            if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[requestedGroup].x != 0) {
                if (requestedGroup == 6) {
                    offset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                    group = requestedGroup;
                } else if (requestedGroup == 5) {
                    offset -= DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                }
                int const assemblyX = DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[group].x;
                int const assemblyY = DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[group].y;
                for (int i = offset; i < 49; ++i) {
                    int const x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].x + assemblyX;
                    int const y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[i].y + assemblyY;
                    int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    int const occupantID = DAT_TileMapState::instance.UnitLayer[tile];
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
            if (DAT_GameState::instance.playerDataArray[playerID].barracks.id <= 0) {
                return FALSE;
            }
            if (requestedGroup == 6) {
                if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[5].x != 0) {
                    offset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                }
            } else if (requestedGroup == 5) {
                if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[6].x != 0) {
                    offset -= DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                }
            }
            for (int i = offset; i < 72; ++i) {
                int const x
                    = DAT_GameState::instance.playerDataArray[playerID].barracksParadegroundLocations[group][i].x;
                int const y
                    = DAT_GameState::instance.playerDataArray[playerID].barracksParadegroundLocations[group][i].y;
                if ((uint)x > 399 || (uint)y > 399
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                    continue;
                }
                int const occupantID
                    = DAT_TileMapState::instance
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
