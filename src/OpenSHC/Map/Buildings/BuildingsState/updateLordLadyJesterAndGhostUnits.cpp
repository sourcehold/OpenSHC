#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::AI::AIType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040FC40
        void BuildingsState::updateLordLadyJesterAndGhostUnits(int playerID)
        {
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference,
                DAT_GameState::ptr)(playerID, 0);
            int keepID = DAT_GameState::instance.playerDataArray[playerID].keep.id;
            int campgroundX = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;
            int campgroundY = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry - 1;
            if (keepID != 0 && DAT_BuildingsState::instance.buildings[keepID].buildingType == BT_MANORHOUSE) {
                ++campgroundY;
            }

            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                if (keepID <= 0 || DAT_GameState::instance.playerDataArray[playerID].playerDeathRelated != 0) {
                    // Without a keep the lord and his court die
                    int ladyID = DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk;
                    if (ladyID != 0) {
                        DAT_UnitsState::instance.units[ladyID].dying = 1;
                        DAT_UnitsState::instance.units[ladyID].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[ladyID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
                        DAT_UnitsState::instance.units[ladyID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                        DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk = 0;
                    }
                    int lordID = DAT_GameState::instance.playerDataArray[playerID].lordID;
                    if (lordID != 0) {
                        DAT_UnitsState::instance.units[lordID].dying = 1;
                        DAT_UnitsState::instance.units[lordID].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[lordID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
                        DAT_UnitsState::instance.units[lordID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                        DAT_GameState::instance.playerDataArray[playerID].lordID = 0;
                    }
                    int jesterID = DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk;
                    if (jesterID != 0) {
                        DAT_UnitsState::instance.units[jesterID].dying = 1;
                        DAT_UnitsState::instance.units[jesterID].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[jesterID].state.generic
                            = OpenSHC::Map::Units::States::US_DEATH_03;
                        DAT_UnitsState::instance.units[jesterID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                        DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk = 0;
                    }
                    int ghostID = DAT_GameState::instance.playerDataArray[playerID].someUnitID01;
                    if (ghostID == 0) {
                        return;
                    }
                    DAT_GameState::instance.playerDataArray[playerID].someUnitID01 = 0;
                    DAT_UnitsState::instance.units[ghostID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[ghostID].dying = 1;
                    DAT_UnitsState::instance.units[ghostID].state.generic = (UnitState)2;
                    return;
                }
            } else if (DAT_GameCore::instance.mapU4Int0 != 0
                && playerID == DAT_GameState::instance.mapAndTime.somePlayerID) {
                return;
            }

            // The lady, lord and jester stay at the keep
            int ladyID = DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk;
            if (ladyID == 0 && DAT_GameState::instance.mapAndTime.unitLadyRelated != 0) {
                ladyID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    playerID, playerID, campgroundX * 8, campgroundY * 8, this->buildings[keepID].terrainHeightUnk,
                    OpenSHC::Map::Units::UT_LADY);
                if (ladyID != 0) {
                    DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef
                        = DAT_UnitsState::instance.units[ladyID].uid;
                    DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk = ladyID;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                        ladyID);
                    DAT_UnitsState::instance.units[ladyID].state.generic = (UnitState)2;
                }
            }
            if (ladyID != 0) {
                if (DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef
                    != DAT_UnitsState::instance.units[ladyID].uid) {
                    DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk = 0;
                    DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef = 0;
                } else {
                    DAT_UnitsState::instance.units[ladyID].workplaceBuildingID_1 = keepID;
                    DAT_UnitsState::instance.units[ladyID].targetX_2 = campgroundX;
                    DAT_UnitsState::instance.units[ladyID].targetY_2 = campgroundY;
                }
            }

            int lordID = DAT_GameState::instance.playerDataArray[playerID].lordID;
            if (lordID == 0) {
                lordID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    playerID, playerID, campgroundX * 8, campgroundY * 8, this->buildings[keepID].terrainHeightUnk,
                    OpenSHC::Map::Units::UT_LORD);
                if (lordID != 0) {
                    DAT_GameState::instance.playerDataArray[playerID].lordUID
                        = DAT_UnitsState::instance.units[lordID].uid;
                    DAT_GameState::instance.playerDataArray[playerID].lordID = lordID;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                        lordID);
                    DAT_UnitsState::instance.units[lordID].state.generic = (UnitState)2;
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                                DAT_GameSynchronyState::ptr)(playerID)
                            == 1) {
                            DAT_UnitsState::instance.units[lordID].unknownLordTypeBasedMissionSpecificValue_01 = 1;
                        }
                        if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                                DAT_GameSynchronyState::ptr)(playerID)
                            != FALSE) {
                            // The health of AI lords depends on the AI character
                            DAT_UnitsState::instance.units[lordID].maxHealthRatingLord
                                = DAT_SkirmishDefinedData::instance
                                      .MaxLordHealthMapping[DAT_GameState::instance.playerDataArray[playerID].aiType
                                          - 1]
                                      .aiTypeA;
                            DAT_UnitsState::instance.units[lordID].health
                                = DAT_UnitsState::instance.units[lordID].health
                                * DAT_SkirmishDefinedData::instance
                                      .MaxLordHealthMapping[DAT_GameState::instance.playerDataArray[playerID].aiType
                                          - 1]
                                      .maxHealthMultiplier
                                / 100;
                            DAT_UnitsState::instance.units[lordID].maxHealth
                                = DAT_UnitsState::instance.units[lordID].maxHealth
                                * DAT_SkirmishDefinedData::instance
                                      .MaxLordHealthMapping[DAT_GameState::instance.playerDataArray[playerID].aiType
                                          - 1]
                                      .maxHealthMultiplier
                                / 100;
                        }
                    } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                        && DAT_GameCore::instance.selectedLordType_2Unk == 1) {
                        DAT_UnitsState::instance.units[lordID].unknownLordTypeBasedMissionSpecificValue_01 = 1;
                    }
                }
            }
            if (lordID != 0) {
                if (DAT_GameState::instance.playerDataArray[playerID].lordUID
                    != DAT_UnitsState::instance.units[lordID].uid) {
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                        && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_JUST_BUILD) {
                        DAT_GameState::instance.playerDataArray[playerID].lordID = 0;
                        DAT_GameState::instance.playerDataArray[playerID].lordUID = 0;
                    }
                } else {
                    DAT_UnitsState::instance.units[lordID].workplaceBuildingID_1 = keepID;
                    DAT_UnitsState::instance.units[lordID].targetX_2 = campgroundX;
                    DAT_UnitsState::instance.units[lordID].targetY_2 = campgroundY;
                }
            }

            int jesterID = DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk;
            if (jesterID == 0 && DAT_GameState::instance.mapAndTime.unitJesterRelated != 0) {
                jesterID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    playerID, playerID, campgroundX * 8, campgroundY * 8, this->buildings[keepID].terrainHeightUnk,
                    OpenSHC::Map::Units::UT_JESTER);
                if (jesterID != 0) {
                    DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk = jesterID;
                    DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef_2
                        = DAT_UnitsState::instance.units[jesterID].uid;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                        jesterID);
                    DAT_UnitsState::instance.units[jesterID].state.generic = (UnitState)2;
                }
            }
            if (jesterID != 0) {
                if (DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef_2
                    != DAT_UnitsState::instance.units[jesterID].uid) {
                    DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk = 0;
                    DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef_2 = 0;
                } else {
                    DAT_UnitsState::instance.units[jesterID].workplaceBuildingID_1 = keepID;
                    DAT_UnitsState::instance.units[jesterID].targetX_2 = campgroundX;
                    DAT_UnitsState::instance.units[jesterID].targetY_2 = campgroundY;
                }
            }

            // In solitary a ghost haunts the shrine of a populated castle
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                || playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            int shrineID
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    this)(playerID, BT_SHRINE);
            if (shrineID <= 0 || DAT_GameState::instance.playerDataArray[playerID].currentPopulation < 40) {
                return;
            }
            int ghostID = DAT_GameState::instance.playerDataArray[playerID].someUnitID01;
            if (ghostID == 0) {
                ghostID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    playerID, playerID, this->buildings[shrineID].buildingEntryX * 8,
                    this->buildings[shrineID].buildingEntryY * 8, this->buildings[shrineID].terrainHeightUnk,
                    OpenSHC::Map::Units::UT_GHOST);
                if (ghostID == 0) {
                    return;
                }
                DAT_GameState::instance.playerDataArray[playerID].someUnitID01 = ghostID;
                DAT_GameState::instance.playerDataArray[playerID].field714_0x22cc
                    = DAT_UnitsState::instance.units[ghostID].uid;
                DAT_UnitsState::instance.units[ghostID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[ghostID].disappearFadeAlphaCountdown = 32;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].field714_0x22cc
                != DAT_UnitsState::instance.units[ghostID].uid) {
                DAT_GameState::instance.playerDataArray[playerID].someUnitID01 = 0;
                DAT_GameState::instance.playerDataArray[playerID].field714_0x22cc = 0;
                return;
            }
            DAT_UnitsState::instance.units[ghostID].workplaceBuildingID_1 = shrineID;
            DAT_UnitsState::instance.units[ghostID].targetX_2 = this->buildings[shrineID].buildingEntryX;
            DAT_UnitsState::instance.units[ghostID].targetY_2 = this->buildings[shrineID].buildingEntryY;
        }

    }
}
}
