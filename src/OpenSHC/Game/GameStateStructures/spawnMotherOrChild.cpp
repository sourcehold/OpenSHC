#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00458280
    void GameStateStructures::spawnMotherOrChild()
    {
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            return;
        }
        for (int playerID = 1; playerID < 9; playerID++) {
            /*
              if has keep and campground
             */
            if ((this->playerDataArray[playerID].keep.id <= 0)
                || (this->playerDataArray[playerID].campground.id <= 0)) {
                continue;
            }
            /*
              Only spawn in non-multiplayer
             */
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (DAT_GameState::instance.playerDataArray[playerID].someCount46 != 0) {
                    /*
                      if total enemy troop value < 101
                     */
                    if (DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue > 100) {
                        DAT_GameState::instance.playerDataArray[playerID].someCount46 = 0;
                        continue;
                    }
                } else {
                    /*
                      if total enemy troop value < 41
                     */
                    if (DAT_GameState::instance.playerDataArray[playerID].totalEnemyTroopValue > 40) {
                        continue;
                    }
                    DAT_GameState::instance.playerDataArray[playerID].someCount46 = 1;
                }
            } else if (this->playerDataArray[playerID].sumOfTotalEnemyUnitsCount > 0) {
                continue;
            }
            int spawnBudget
                = (75 - this->playerDataArray[playerID].someCount03) - this->playerDataArray[playerID].someCount02;
            for (int buildingID = 0; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; buildingID++) {
                if ((DAT_BuildingsState::instance.buildings[buildingID].logicalState == ((BuildingLogicalState)0))
                    || (DAT_BuildingsState::instance.buildings[buildingID].logicalState
                        == OpenSHC::Map::Buildings::BLS_REMOVE)
                    || (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID)
                    || (DAT_BuildingsState::instance.buildings[buildingID].fireDuration != 0)
                    || ((DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            != OpenSHC::Map::Buildings::BT_HOVEL)
                        && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                            != OpenSHC::Map::Buildings::BT_HOUSE))) {
                    continue;
                }
                if (spawnBudget <= 0) {
                    break;
                }
                /*
                  if building has no unit
                 */
                if (DAT_BuildingsState::instance.buildings[buildingID].unitRefID == 0) {
                    short motherEntryX = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
                    if (motherEntryX > 0) {
                        short motherEntryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
                        if (motherEntryY > 0) {
                            int motherTile
                                = DAT_ViewportRenderState::instance.translationMatrix[motherEntryY].addXgetTile
                                + motherEntryX;
                            int motherUnitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                                DAT_UnitsState::ptr)(playerID, playerID, motherEntryX * 8, motherEntryY * 8,
                                DAT_TileMapState::instance.HeightLayer[motherTile], OpenSHC::Map::Units::UT_MOTHER);
                            if (motherUnitID != 0) {
                                /*
                                  store in unitRef
                                 */
                                DAT_BuildingsState::instance.buildings[buildingID].unitRefID = (short)motherUnitID;
                                DAT_BuildingsState::instance.buildings[buildingID].unitRefUID
                                    = DAT_UnitsState::instance.units[motherUnitID].uid;
                                DAT_UnitsState::instance.units[motherUnitID].workplaceBuildingUID
                                    = DAT_BuildingsState::instance.buildings[buildingID].uid;
                                DAT_UnitsState::instance.units[motherUnitID].workplaceBuildingID_1 = (short)buildingID;
                                spawnBudget = spawnBudget - 1;
                                DAT_BuildingsState::instance.buildings[buildingID].childSpawnCountdown
                                    = (char)((DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 >> 10)
                                          % 3)
                                    + 1;
                            }
                        }
                    }
                } else if (DAT_GameState::instance.playerDataArray[playerID].popularity / 100 >= 50) {
                    /*
                      if popularity is higher than 49
                     */
                    DAT_BuildingsState::instance.buildings[buildingID].childSpawnCountdown
                        = DAT_BuildingsState::instance.buildings[buildingID].childSpawnCountdown - 1;
                    if (((char)DAT_BuildingsState::instance.buildings[buildingID].childSpawnCountdown <= 0)
                        && ((short)(char)DAT_BuildingsState::instance.buildings[buildingID].maxOccupants
                            != DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount)) {
                        short childEntryX = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
                        DAT_BuildingsState::instance.buildings[buildingID].childSpawnCountdown
                            = (char)((DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1 >> 10) % 3)
                            + 1;
                        if (childEntryX > 0) {
                            short childEntryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
                            if (childEntryY > 0) {
                                int childTile
                                    = DAT_ViewportRenderState::instance.translationMatrix[childEntryY].addXgetTile
                                    + childEntryX;
                                int childUnitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                                    DAT_UnitsState::ptr)(playerID, playerID, childEntryX * 8, childEntryY * 8,
                                    DAT_TileMapState::instance.HeightLayer[childTile], OpenSHC::Map::Units::UT_CHILD);
                                if (childUnitID != 0) {
                                    spawnBudget = spawnBudget - 1;
                                    DAT_BuildingsState::instance.buildings[buildingID]
                                        .workerID[DAT_BuildingsState::instance.buildings[buildingID]
                                                .currentEmployeeCount] = (short)childUnitID;
                                    DAT_BuildingsState::instance.buildings[buildingID].workerUID
                                        [DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount]
                                        = DAT_UnitsState::instance.units[childUnitID].uid;
                                    int workplaceUID = DAT_BuildingsState::instance.buildings[buildingID].uid;
                                    /*
                                      increment currentEmployeeCount of building
                                     */
                                    DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount
                                        = DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount + 1;
                                    DAT_UnitsState::instance.units[childUnitID].workplaceBuildingID_1
                                        = (short)buildingID;
                                    DAT_UnitsState::instance.units[childUnitID].workplaceBuildingUID = workplaceUID;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
}
