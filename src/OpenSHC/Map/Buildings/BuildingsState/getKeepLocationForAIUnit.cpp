#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D9C0
        BOOLEnum BuildingsState::getKeepLocationForAIUnit(int playerID, int group, int unitID)
        {
            // group is the mercenary group (10 to 16); it is remapped while mercenaryType keeps the original value.
            int const mercenaryType = group;
            // AI units in multiplayer gather at the keep
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0
                && DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2) {
                int const keepID = DAT_GameState::instance.playerDataArray[playerID]
                                       .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                                       .id;
                if (keepID == 0) {
                    return FALSE;
                }
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[keepID].someX;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[keepID].someY;
                return TRUE;
            }

            if (mercenaryType == 16) {
                group = 13;
            }
            // Note: indexes past the declared size of rallySearchOffsetsUnk
            int searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffsetsUnk[group];
            if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[mercenaryType - 10][0] != 0) {
                // Search around the rally point
                if (mercenaryType == 16) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].someCount23;
                    group = mercenaryType;
                } else if (mercenaryType == 13) {
                    searchOffset -= DAT_GameState::instance.playerDataArray[playerID].someCount23;
                }
                int const pointX
                    = DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[group - 10][0];
                int const pointY
                    = DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[group - 10][1];
                for (; searchOffset < countof(DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1);
                    ++searchOffset) {
                    int const x = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].x + pointX;
                    int const y = DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[searchOffset].y + pointY;
                    int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                    int const unitOnTile = DAT_TileMapState::instance.UnitLayer[tile];
                    if (unitOnTile != 0 && unitOnTile != unitID
                        && DAT_UnitsState::instance.units[unitID].movementRelated == 8) {
                        continue;
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                              calculateCanPlayerUnitsNavigateToAreaFromArea,
                            DAT_PathFindingState::ptr)(playerID,
                            DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile],
                            DAT_TileMapState::instance.PathConnectionLayer[tile], 0)
                        == 0) {
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
                // Matching note: this explicit return lets MSVC cross-jump the position test into the parade ground
                // loop
                return FALSE;
            }

            // No rally point, use the parade ground of the mercenary post
            if (DAT_GameState::instance.playerDataArray[playerID]
                    .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                    .id
                <= 0) {
                return FALSE;
            }
            if (mercenaryType == 16) {
                if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[3][0] != 0) {
                    searchOffset = DAT_GameState::instance.playerDataArray[playerID].someCount23;
                }
            } else if (mercenaryType == 13
                // Note: the original reads index 16 instead of 16 - 10
                && DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[16][0] != 0) {
                searchOffset -= DAT_GameState::instance.playerDataArray[playerID].someCount23;
            }
            // The 3 x 24 locations of one group are read as one run of 72
            for (int i = searchOffset; i < 72; ++i) {
                int const x = DAT_GameState::instance.playerDataArray[playerID]
                                  .structure.mercenaryOutpostCampgroundLocations[group - 10][0][i]
                                  .x;
                int const y = DAT_GameState::instance.playerDataArray[playerID]
                                  .structure.mercenaryOutpostCampgroundLocations[group - 10][0][i]
                                  .y;
                int const unitOnTile
                    = DAT_TileMapState::instance
                          .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                if (unitOnTile != 0 && unitOnTile != unitID
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
