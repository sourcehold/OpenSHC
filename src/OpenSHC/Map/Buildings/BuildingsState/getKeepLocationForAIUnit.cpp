#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

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

        using OpenSHC::Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D9C0
        undefined4 BuildingsState::getKeepLocationForAIUnit(int playerID, int param_2, int unitID)
        {
            // Matching note: The remaining differences are register allocation; the original also does not
            // constant propagate group = 16 in the rally branch.
            int group = param_2;
            // AI units in multiplayer gather at the keep
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0
                && DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2) {
                int keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
                if (keepID == 0) {
                    return 0;
                }
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[keepID].someX;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[keepID].someY;
                return 1;
            }

            // param_2 is the mercenary group (10 to 16)
            if (param_2 == 16) {
                group = 13;
            }
            // Note: indexes past the declared size of rallySearchOffsetsUnk
            int searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffsetsUnk[group];
            if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[param_2 - 10][0] != 0) {
                // Search around the rally point
                if (param_2 == 16) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].someCount23;
                    group = param_2;
                } else if (param_2 == 13) {
                    searchOffset -= DAT_GameState::instance.playerDataArray[playerID].someCount23;
                }
                int pointX
                    = (short)DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[group - 10][0];
                int pointY
                    = (short)DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[group - 10][1];
                for (; searchOffset < 49; ++searchOffset) {
                    int y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].y + pointY;
                    int x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].x + pointX;
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
            } else {
                // No rally point, use the parade ground of the mercenary post
                if (DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id > 0) {
                    if (param_2 == 16) {
                        if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[3][0] != 0) {
                            searchOffset = DAT_GameState::instance.playerDataArray[playerID].someCount23;
                        }
                    } else if (param_2 == 13
                        // Note: the original reads index 16 instead of 16 - 10
                        && DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[16][0] != 0) {
                        searchOffset -= DAT_GameState::instance.playerDataArray[playerID].someCount23;
                    }
                    int x;
                    int y;
                    for (;; ++searchOffset) {
                        if (searchOffset >= 72) {
                            return 0;
                        }
                        y = DAT_GameState::instance.playerDataArray[playerID]
                                .structure.mercenaryOutpostCampgroundLocations[(group - 10) * 72 + searchOffset]
                                .y;
                        x = DAT_GameState::instance.playerDataArray[playerID]
                                .structure.mercenaryOutpostCampgroundLocations[(group - 10) * 72 + searchOffset]
                                .x;
                        if ((short)DAT_TileMapState::instance
                                    .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                                == 0
                            || (short)DAT_TileMapState::instance
                                    .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                                == unitID
                            || DAT_UnitsState::instance.units[unitID].movementRelated != 8) {
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
            }
            return 0;
        }

    }
}
}
