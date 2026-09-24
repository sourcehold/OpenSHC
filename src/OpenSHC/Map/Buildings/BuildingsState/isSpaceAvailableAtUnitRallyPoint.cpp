#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D6E0
        undefined4 BuildingsState::isSpaceAvailableAtUnitRallyPoint(int playerID, int value0to6, int unitID)
        {
            // AI units in multiplayer gather at the keep
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0
                && DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2) {
                if (DAT_GameState::instance.playerDataArray[playerID].keep.id == 0) {
                    return 0;
                }
                this->DAT_TempXOffset
                    = this->buildings[DAT_GameState::instance.playerDataArray[playerID].keep.id].someX;
                this->DAT_TempYOffset
                    = this->buildings[DAT_GameState::instance.playerDataArray[playerID].keep.id].someY;
                return 1;
            }

            int group = value0to6;
            if (value0to6 == 6) {
                group = 5;
            }
            int searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffsetsUnk[group];
            if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[value0to6].x == 0) {
                // No rally point, use the parade ground of the barracks
                if (DAT_GameState::instance.playerDataArray[playerID].barracks.id > 0) {
                    if (value0to6 == 6) {
                        if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[5].x != 0) {
                            searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                        }
                    } else if (value0to6 == 5
                        && DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[6].x != 0) {
                        searchOffset -= DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                    }
                    uint x;
                    uint y;
                    for (;; ++searchOffset) {
                        if (searchOffset >= 72) {
                            return 0;
                        }
                        x = DAT_GameState::instance.playerDataArray[playerID]
                                .barracksParadegroundLocations[group][searchOffset]
                                .x;
                        y = DAT_GameState::instance.playerDataArray[playerID]
                                .barracksParadegroundLocations[group][searchOffset]
                                .y;
                        if (x <= 399 && y <= 399
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0
                            && ((short)DAT_TileMapState::instance
                                        .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile
                                            + x]
                                    == 0
                                || (short)DAT_TileMapState::instance
                                        .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile
                                            + x]
                                    == unitID
                                || DAT_UnitsState::instance.units[unitID].movementRelated != 8)) {
                            break;
                        }
                    }
                    this->DAT_TempXOffset = x;
                    this->DAT_TempYOffset = y;
                    if (x == DAT_UnitsState::instance.units[unitID].x
                        && y == DAT_UnitsState::instance.units[unitID].y) {
                        return 0;
                    }
                    return 1;
                }
            } else {
                // Search around the rally point
                if (value0to6 == 6) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                    group = value0to6;
                } else if (value0to6 == 5) {
                    searchOffset -= DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
                }
                short pointX = DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[group].x;
                short pointY = DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[group].y;
                for (; searchOffset < 49; ++searchOffset) {
                    uint y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].y + pointY;
                    uint x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].x + pointX;
                    int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    if (((short)DAT_TileMapState::instance.UnitLayer[tile] == 0
                            || (short)DAT_TileMapState::instance.UnitLayer[tile] == unitID
                            || DAT_UnitsState::instance.units[unitID].movementRelated != 8)
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                 calculateCanPlayerUnitsNavigateToAreaFromArea,
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
            }
            return 0;
        }

    }
}
}
