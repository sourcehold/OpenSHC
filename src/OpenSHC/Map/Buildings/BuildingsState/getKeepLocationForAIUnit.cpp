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
        BOOLEnum BuildingsState::getKeepLocationForAIUnit(int playerID, int group, int unitID)
        {
            // Matching note: The parameter is the adjusted group and a copy keeps the requested one (as in the
            // original, and in isSpaceAvailableAtUnitRallyPoint); the tile's unit is read once into an int. The rest is
            // register allocation and one return block the original shares.
            // group is the mercenary group (10 to 16)
            int const requestedGroup = group;
            // AI units in multiplayer gather at the keep
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0
                && DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2) {
                int keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
                if (keepID == 0) {
                    return FALSE;
                }
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[keepID].someX;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[keepID].someY;
                return TRUE;
            }

            if (requestedGroup == 16) {
                group = 13;
            }
            // Note: indexes past the declared size of rallySearchOffsetsUnk
            int searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffsetsUnk[group];
            if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[requestedGroup - 10][0]
                != 0) {
                // Search around the rally point
                if (requestedGroup == 16) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].someCount23;
                    group = requestedGroup;
                } else if (requestedGroup == 13) {
                    searchOffset -= DAT_GameState::instance.playerDataArray[playerID].someCount23;
                }
                int pointX
                    = (short)DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[group - 10][0];
                int pointY
                    = (short)DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[group - 10][1];
                for (; searchOffset < 49; ++searchOffset) {
                    int x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].x + pointX;
                    int y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].y + pointY;
                    int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    int const occupant = DAT_TileMapState::instance.UnitLayer[tile];
                    if ((occupant == 0 || occupant == unitID
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
                            return FALSE;
                        }
                        return TRUE;
                    }
                }
            } else {
                // No rally point, use the parade ground of the mercenary post
                if (DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id > 0) {
                    if (requestedGroup == 16) {
                        if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[3][0] != 0) {
                            searchOffset = DAT_GameState::instance.playerDataArray[playerID].someCount23;
                        }
                    } else if (requestedGroup == 13
                        // Note: the original reads index 16 instead of 16 - 10
                        && DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[16][0] != 0) {
                        searchOffset -= DAT_GameState::instance.playerDataArray[playerID].someCount23;
                    }
                    // The search runs across the three 24-entry pieces, so the formation is read as 72 flat slots.
                    for (; searchOffset < 72; ++searchOffset) {
                        int const x = (&DAT_GameState::instance.playerDataArray[playerID]
                                .structure
                                .mercenaryOutpostCampgroundLocations[0][0][0])[(group - 10) * 72 + searchOffset]
                                          .x;
                        int const y = (&DAT_GameState::instance.playerDataArray[playerID]
                                .structure
                                .mercenaryOutpostCampgroundLocations[0][0][0])[(group - 10) * 72 + searchOffset]
                                          .y;
                        int const occupant
                            = DAT_TileMapState::instance
                                  .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                        if (occupant != 0 && occupant != unitID
                            && DAT_UnitsState::instance.units[unitID].movementRelated == 8) {
                            continue;
                        }
                        this->DAT_TempXOffset = x;
                        this->DAT_TempYOffset = y;
                        if (x == DAT_UnitsState::instance.units[unitID].x
                            && y == DAT_UnitsState::instance.units[unitID].y) {
                            return FALSE;
                        }
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
