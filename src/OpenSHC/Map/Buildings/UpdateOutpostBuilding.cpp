#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00411540
    void Buildings::UpdateOutpostBuilding()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].someCount04 += 10;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage
                          / 2];
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            return;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0
            && DAT_GameSynchronyState::instance.currentGameMode != 99
            && DAT_GameState::instance.mapAndTime.skirmishNoRushTicks != 0) {
            return;
        }

        // AI units around a new outpost join it as garrison
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].surroundingsRevealed == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].surroundingsRevealed = 1;
            int const half
                = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].widthOrHeight / 2;
            int const centerX = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x + half;
            int const xEnd = centerX + 8;
            int const centerY = half + DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y;
            int const yEnd = centerY + 8;
            int const yStart = centerY - 8;
            for (int x = centerX - 8; x < xEnd; ++x) {
                for (int y = yStart; y < yEnd; ++y) {
                    // Faithful to the original, which tests the map cell at (x, x) rather than (x, y)
                    if ((uint)x <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[x * 400 + x] != 0) {
                        int unitID
                            = DAT_TileMapState::instance
                                  .UnitLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                        while (unitID != 0) {
                            if (DAT_UnitsState::instance.units[unitID].owner
                                == DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner) {
                                // AI behaviour type 50 has no AIUnitBehaviourType constant.
                                DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 50;
                            }
                            unitID = DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile;
                        }
                    }
                }
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3 > 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3 -= 1;
        }
        int tribeID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeID;
        int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex;
        if (tribeID != 0
            && DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeUID) {
            tribeID = 0;
        }

        // Keep 6-7 archers in the outpost's garrison slots
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].randomOutpostField > 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 -= 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 < 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 = 1200;
                int aliveUnits = 0;
                for (int i = 0; i < 4; ++i) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].insideUnitID[i] > 0
                        && DAT_UnitsState::instance
                                .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .insideUnitID[i]]
                                .uid
                            == DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                .insideUnitUID[i]) {
                        aliveUnits += 1;
                    }
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[i] > 0
                        && DAT_UnitsState::instance
                                .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .workerID[i]]
                                .uid
                            == DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[i]) {
                        aliveUnits += 1;
                    }
                }
                if (aliveUnits
                    < DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].randomOutpostField) {
                    int archerType = OpenSHC::Map::Units::UT_E_ARCHER;
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingType
                        == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN) {
                        archerType = OpenSHC::Map::Units::UT_A_ARCHER;
                    }
                    int const unitID
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX * 8,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY * 8,
                            8, (OpenSHC::Map::Units::UnitType)archerType);
                    if (unitID != 0) {
                        DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 50;
                        DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
                        DAT_UnitsState::instance.units[unitID].state.generic
                            = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                        int destinationX = -1;
                        int destinationY = -1;
                        for (int attempt = 0; attempt < 15; ++attempt) {
                            int const x = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                                + (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .widthOrHeight
                                    / 2
                                + SEC_RNG::instance.currentNumber2 % 14 - 7;
                            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                            int const y = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                              .widthOrHeight
                                    / 2
                                + DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y
                                + SEC_RNG::instance.currentNumber2 % 14 - 7;
                            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                            if ((uint)x > 399 || (uint)y > 399
                                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                                continue;
                            }
                            int const unitArea
                                = (short)DAT_TileMapState::instance.PathConnectionLayer
                                      [DAT_ViewportRenderState::instance
                                              .translationMatrix[DAT_UnitsState::instance.units[unitID].y]
                                              .addXgetTile
                                          + DAT_UnitsState::instance.units[unitID].x];
                            int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                            int const targetArea = (short)DAT_TileMapState::instance.PathConnectionLayer[tile];
                            if (unitArea != targetArea
                                && !MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                          calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].owner, unitArea,
                                    targetArea, DAT_UnitsState::instance.units[unitID].unitCanClimb)) {
                                continue;
                            }
                            if (destinationX < 0) {
                                destinationX = x;
                                destinationY = y;
                            }
                            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x10000000) != 0) {
                                destinationX = x;
                                destinationY = y;
                                break;
                            }
                        }
                        if (destinationX >= 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                DAT_UnitsState::ptr)(unitID, destinationX, destinationY, 0);
                        }
                        for (int i = 0; i < 4; ++i) {
                            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].insideUnitID[i]
                                    <= 0
                                || DAT_UnitsState::instance
                                        .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                                .insideUnitID[i]]
                                        .uid
                                    != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .insideUnitUID[i]) {
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].insideUnitID[i]
                                    = unitID;
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].insideUnitUID[i]
                                    = DAT_UnitsState::instance.units[unitID].uid;
                                break;
                            }
                            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[i] <= 0
                                || DAT_UnitsState::instance
                                        .units[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                                .workerID[i]]
                                        .uid
                                    != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                        .workerUID[i]) {
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[i]
                                    = unitID;
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[i]
                                    = DAT_UnitsState::instance.units[unitID].uid;
                                break;
                            }
                        }
                    }
                }
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].randomOutpostField
                = SEC_RNG::instance.currentNumber2 % 2 + 6;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 = 1200;
        }

        // Without a live tribe, wait, then pick one of the unit types enabled in outpostRelatedUnk1 and start a tribe
        if (tribeID == 0) {
            int delay
                = 2000 - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk06;
            if (DAT_GameSynchronyState::instance.currentGameMode != 0
                && DAT_GameSynchronyState::instance.currentGameMode != 99) {
                if (delay < 400) {
                    delay = 400;
                }
            } else if (delay < 100) {
                delay = 100;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field220_0x308 += 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field220_0x308 < delay) {
                return;
            }
            int const mask
                = (ushort)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk1;
            int enabledTypes = 0;
            if ((mask & 1) != 0) {
                enabledTypes += 1;
            }
            if ((mask & 2) != 0) {
                enabledTypes += 1;
            }
            if ((mask & 4) != 0) {
                enabledTypes += 1;
            }
            if ((mask & 8) != 0) {
                enabledTypes += 1;
            }
            if ((mask & 16) != 0) {
                enabledTypes += 1;
            }
            if ((mask & 32) != 0) {
                enabledTypes += 1;
            }
            if ((mask & 64) != 0) {
                enabledTypes += 1;
            }
            if ((mask & 128) != 0) {
                enabledTypes += 1;
            }
            if (enabledTypes == 0) {
                return;
            }
            int const pick = SEC_RNG::instance.currentNumber2 % enabledTypes;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            int choice = 0;
            if ((mask & 1) != 0) {
                if (pick == choice) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 0;
                }
                choice += 1;
            }
            if ((mask & 2) != 0) {
                if (pick == choice) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 1;
                }
                choice += 1;
            }
            if ((mask & 4) != 0) {
                if (pick == choice) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 2;
                }
                choice += 1;
            }
            if ((mask & 8) != 0) {
                if (pick == choice) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 3;
                }
                choice += 1;
            }
            if ((mask & 16) != 0) {
                if (pick == choice) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 4;
                }
                choice += 1;
            }
            if ((mask & 32) != 0) {
                if (pick == choice) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 5;
                }
                choice += 1;
            }
            if ((mask & 64) != 0) {
                if (pick == choice) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 6;
                }
                choice += 1;
            }
            if ((mask & 128) != 0) {
                if (pick == choice) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex = 7;
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingType
                == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex += 8;
            }
            index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spawnUnitTypeIndex;
            tribeID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer,
                DAT_TribesState::ptr)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner);
            if (tribeID <= 0) {
                return;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeID = tribeID;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeUID
                = DAT_TribesState::instance.tribes[tribeID].uid;
            DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk05
                = (SEC_RNG::instance.currentNumber2 % DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][3]
                      + DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][2])
                * (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk2 + 1);
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field225_0x312 = 1;
            DAT_TribesState::instance.tribes[tribeID].tribeSubtype1
                = DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][12];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field220_0x308 = 2000;
        }

        // Grow the tribe one batch at a time, then send it off once it is full
        int interval = DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][0]
            - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].incByFourUnk;
        if (interval < DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][1]) {
            interval = DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][1];
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0
            && DAT_GameSynchronyState::instance.currentGameMode != 99 && interval < 50) {
            interval = 50;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field220_0x308 += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field220_0x308
            < (100 - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk2 * 15)
                * interval / 100) {
            return;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field220_0x308
            = SEC_RNG::instance.currentNumber2 % 40;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3 > 0
            && DAT_TribesState::instance.tribes[tribeID].size
                >= DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk05 - 1) {
            return;
        }
        int choices = 0;
        if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][4] != 0) {
            choices += 1;
        }
        if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][5] != 0) {
            choices += 1;
        }
        if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][6] != 0) {
            choices += 1;
        }
        if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][7] != 0) {
            choices += 1;
        }
        if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][8] != 0) {
            choices += 1;
        }
        if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][9] != 0) {
            choices += 1;
        }
        if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][10] != 0) {
            choices += 1;
        }
        if (DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][11] != 0) {
            choices += 1;
        }
        if (index == 7 || index == 6) {
            if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3 == 0
                    && DAT_TribesState::instance.tribes[tribeID].size == 0)
                || (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field225_0x312 != 0
                    && DAT_TribesState::instance.tribes[tribeID].size > 0)) {
                choices = 1;
            }
        }
        int unitType = DAT_BuildingDefinedData::instance
                           .SpawnUnitProperties[index][4 + SEC_RNG::instance.currentNumber2 % choices];
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        int batchSize = 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3 > 0
            && DAT_TribesState::instance.tribes[tribeID].size == 0
            && DAT_GameState::instance.playerDataArray[owner].aiType != 0) {
            batchSize = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk05 / 2;
            if (batchSize == 0) {
                batchSize = 1;
            }
            if ((index == 7 || index == 6) && batchSize > 1 && unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                unitType = DAT_BuildingDefinedData::instance.SpawnUnitProperties[index][5];
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0
            && DAT_GameSynchronyState::instance.currentGameMode != 99
            && DAT_GameState::instance.playerDataArray[owner].count_2
                    + DAT_GameState::instance.playerDataArray[owner].armySize
                >= DAT_GameState::instance.mapAndTime.armySizeLimit) {
            return;
        }
        for (int n = 0; n < batchSize; ++n) {
            int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX * 8,
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY * 8, 8,
                (OpenSHC::Map::Units::UnitType)unitType);
            if (unitID == 0) {
                return;
            }
            if (unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field225_0x312 = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                unitID, tribeID);
            // Siege engines come with their crew of engineers
            int crew = 0;
            switch (unitType) {
            case OpenSHC::Map::Units::UT_S_CATAPULT:
                crew = 2;
                break;
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                crew = 3;
                break;
            case OpenSHC::Map::Units::UT_S_TOWER:
            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                crew = 4;
                break;
            case OpenSHC::Map::Units::UT_S_SHIELD:
                crew = 1;
                break;
            }
            for (int i = 0; i < crew; ++i) {
                int const engineerID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit,
                    DAT_UnitsState::ptr)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX * 8,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY * 8, 8,
                    OpenSHC::Map::Units::UT_E_ENGINEER);
                if (engineerID != 0) {
                    DAT_UnitsState::instance.units[engineerID].targetingType
                        = OpenSHC::Map::Units::UIT_MAN_SIEGE_EQUIPMENT;
                    DAT_UnitsState::instance.units[engineerID].targetedUnitID__OR__engineerMannedSiegeEngineRef
                        = unitID;
                }
            }
            DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType = 50;
            DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
            tribeID, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX,
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY, 0, 0,
            OpenSHC::Map::Units::Instructions::UMSE_0);
        if (DAT_TribesState::instance.tribes[tribeID].size
                >= DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk05
            && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk3 <= 0) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRegisterTribeAndAssignTarget, DAT_AICState::ptr)(
                tribeID, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeUID);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tribeID = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk06 += 100;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].incByFourUnk += 4;
        }
    }

}
}
