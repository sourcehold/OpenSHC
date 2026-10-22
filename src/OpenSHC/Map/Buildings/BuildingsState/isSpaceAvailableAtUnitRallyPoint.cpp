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
        undefined4 BuildingsState::isSpaceAvailableAtUnitRallyPoint(int playerID, int group, int unitID)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != 0
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0
                && DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2) {
                int const keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
                if (keepID == 0) {
                    return 0;
                }
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[keepID].someX;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[keepID].someY;
                return 1;
            }
            int index = group;
            if (index == 6) {
                index = 5;
            }
            int offset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffsetsUnk[index];
            if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[group].x != 0) {
                if (group == 6) {
                    offset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                    index = group;
                } else if (group == 5) {
                    offset -= DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                }
                int const assemblyX = DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[index].x;
                int const assemblyY = DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[index].y;
                for (int i = offset; i < 49; ++i) {
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
                            return 0;
                        }
                        return 1;
                    }
                }
                return 0;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].barracks.id <= 0) {
                return 0;
            }
            if (group == 6) {
                if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[5].x != 0) {
                    offset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                }
            } else if (group == 5) {
                if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[6].x != 0) {
                    offset -= DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                }
            }
            for (int i = offset; i < 72; ++i) {
                int const x
                    = DAT_GameState::instance.playerDataArray[playerID].barracksParadegroundLocations[index][i].x;
                int const y
                    = DAT_GameState::instance.playerDataArray[playerID].barracksParadegroundLocations[index][i].y;
                if ((uint)x > 399 || (uint)y > 399
                    || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
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
                    return 0;
                }
                return 1;
            }
            return 0;
        }

    }
}
}
