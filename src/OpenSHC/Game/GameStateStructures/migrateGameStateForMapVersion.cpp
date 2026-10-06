#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::Game::TrailType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045C1C0
    void GameStateStructures::migrateGameStateForMapVersion(
        PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
    {
        if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                && (DAT_GameCore::instance.isSkirmishTrail == TRUE))
            && (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME)) {
            DAT_GameCore::instance.isSkirmishTrail = FALSE;
            DAT_GameCore::instance.currentTrailType = OpenSHC::Game::TT_FIRST_EDITION;
        }
        MACRO_CALL(OpenSHC::Map::Version_Func::ValidateLadyAndJesterUnitRefs)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::recountStablesAndHorses, this)();
        if ((int)receivedMapVersion >= 0x9a) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::MapPropertiesState_Func::pruneInvalidEventTriggerLinks, DAT_MapPropertiesState::ptr)();
        }
        if (receivedMapVersion != packagerMapVersion) {
            if ((int)receivedMapVersion < 0x90) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearActiveClimbDataOfType6And7,
                    DAT_PathFindingState::ptr)();
            }
            if ((int)receivedMapVersion < 0x7a) {
                MACRO_CALL(OpenSHC::Map::Version_Func::InitPopularityAndRecruitableDefaults)();
            }
            if ((int)receivedMapVersion < 0x7b) {
                MACRO_CALL(OpenSHC::Map::Version_Func::ResetTeams)();
            }
            if ((int)receivedMapVersion < 0x7f) {
                for (int buildingType = 0; buildingType < 100; buildingType++) {
                    DAT_MapPropertiesState::instance.buildingAvailability[buildingType] = 1;
                }
            }
            if ((int)receivedMapVersion < 0x82) {
                DAT_GameState::instance.mapAndTime.populationIndex = 0;
                memset(DAT_GameState::instance.mapAndTime.lionLocationsXY, 0,
                    sizeof(DAT_GameState::instance.mapAndTime.lionLocationsXY));
                DAT_GameState::instance.mapAndTime.field2269_0xdee = 0;
                DAT_GameState::instance.mapAndTime.unitLadyRelated = 0;
                DAT_GameState::instance.mapAndTime.unitJesterRelated = 0;
            }
            if ((int)receivedMapVersion < 0x85) {
                for (int unitID = 1; unitID < 2500; unitID++) {
                    if ((DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE)
                        && (DAT_UnitsState::instance.units[unitID].unitType != ((UnitType)0))) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignNameToUnit, DAT_UnitsState::ptr)(
                            unitID);
                    }
                }
                /*
                  clears the 32 fields from field3092_0x2654 up to and including field3123_0x26d0 as one array,
                  exactly as the original binary does
                 */
                for (int index = 0; index < 32; index++) {
                    (&DAT_GameState::instance.mapAndTime.field3092_0x2654)[index] = 0;
                }
            }
            if ((int)receivedMapVersion < 0x87) {
                /*
                  field2_0x8 to field11_0x2c, field12_0x30 to field21_0x54, field22_0x58 and field23_0x80 to
                  field32_0xa4 are four arrays of ten entries that are reset together, exactly as the original
                  binary does
                 */
                for (int index = 0; index < 10; index++) {
                    (&DAT_GameState::instance.mapAndTime.field2_0x8)[index] = 0;
                    (&DAT_GameState::instance.mapAndTime.field12_0x30)[index] = 0;
                    DAT_GameState::instance.mapAndTime.field22_0x58[0][index] = -1;
                    (&DAT_GameState::instance.mapAndTime.field23_0x80)[index] = -1;
                }
            }
            if ((int)receivedMapVersion < 0x88) {
                DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown = 0;
                DAT_GameState::instance.mapAndTime.unk_signpostDistance = 30;
            }
            if ((int)receivedMapVersion < 0x8a) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    DAT_GameState::instance.playerDataArray[playerID].aiControlStatusRelated = -1000;
                }
            }
            if ((int)receivedMapVersion < 0x8b) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    int cowCount = 0;
                    DAT_GameState::instance.playerDataArray[playerID].counter = 0;
                    int siegeEngineCount = 0;
                    for (int unitID = 1; unitID < 2500; unitID++) {
                        if ((DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE)
                            && (DAT_UnitsState::instance.units[unitID].unitType != ((UnitType)0))
                            && (DAT_UnitsState::instance.units[unitID].owner == playerID)) {
                            if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_COW) {
                                cowCount = cowCount + 1;
                            }
                            if ((DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT)
                                || (DAT_UnitsState::instance.units[unitID].unitType
                                    == OpenSHC::Map::Units::UT_S_TREBUCHET)) {
                                siegeEngineCount = siegeEngineCount + 1;
                            }
                        }
                    }
                    if (DAT_GameState::instance.playerDataArray[playerID].keep.id != 0) {
                        DAT_GameState::instance.playerDataArray[playerID].counter = cowCount;
                    } else {
                        DAT_GameState::instance.playerDataArray[playerID].counter = siegeEngineCount;
                    }
                }
            }
            if ((int)receivedMapVersion < 141) {
                /*
                  the four arrays of ten entries starting at field2_0x8, field12_0x30, field22_0x58 and field23_0x80
                  are copied from the ones starting at field3124_0x26d4, field3134_0x26fc, field3144_0x2724 and
                  field3154_0x274c, exactly as the original binary does
                 */
                for (int index = 0; index < 10; index++) {
                    (&DAT_GameState::instance.mapAndTime.field2_0x8)[index]
                        = (&DAT_GameState::instance.mapAndTime.field3124_0x26d4)[index];
                    (&DAT_GameState::instance.mapAndTime.field12_0x30)[index]
                        = (&DAT_GameState::instance.mapAndTime.field3134_0x26fc)[index];
                    DAT_GameState::instance.mapAndTime.field22_0x58[0][index]
                        = (&DAT_GameState::instance.mapAndTime.field3144_0x2724)[index];
                    (&DAT_GameState::instance.mapAndTime.field23_0x80)[index]
                        = (&DAT_GameState::instance.mapAndTime.field3154_0x274c)[index];
                }
            }
            short unitJesterRelated = DAT_GameState::instance.mapAndTime.unitJesterRelated;
            short unitLadyRelated = DAT_GameState::instance.mapAndTime.unitLadyRelated;
            if (((int)receivedMapVersion < 143)
                && (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)) {
                for (int unitID = 1; unitID < 2500; unitID++) {
                    if ((DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE)
                        && (((DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_JESTER)
                                && (unitJesterRelated == 0))
                            || ((DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_LADY)
                                && (unitLadyRelated == 0)))) {
                        DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                    }
                }
            }
            if ((int)receivedMapVersion < 148) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    for (int foodType = 0; foodType < 4; foodType++) {
                        DAT_GameState::instance.playerDataArray[playerID].isFoodTypeBanned[foodType] = 0;
                    }
                }
            }
            if ((int)receivedMapVersion < 0x99) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::resetEuroUnitRestrictions, DAT_MapPropertiesState::ptr)();
            }
            if ((int)receivedMapVersion < 0x9a) {
                MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::removeProcessedInvasionEvents,
                    DAT_MapPropertiesState::ptr)();
            }
            if ((int)receivedMapVersion < 0x9c) {
                for (int playerID = 0; playerID < 9; playerID++) {
                    DAT_GameState::instance.playerDataArray[playerID].sumOfTotalEnemyUnitsCount
                        = DAT_GameState::instance.playerDataArray[playerID].enemies;
                }
                DAT_GameState::instance.mapAndTime.skirmishStrongWalls = 0;
                DAT_GameState::instance.mapAndTime.skirmishAlliances = 0;
            }
            if ((int)receivedMapVersion < 0x9e) {
                for (int playerID = 0; playerID < 9; playerID++) {
                    for (int assemblyPoint = 0; assemblyPoint < 7; assemblyPoint++) {
                        DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[assemblyPoint].x = 0;
                        DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[assemblyPoint].y = 0;
                    }
                }
            }
            if ((int)receivedMapVersion < 0xa2) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[playerID] = 0;
                    for (int buildingSlot = 0; buildingSlot < 2000; buildingSlot++) {
                        DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[playerID][buildingSlot] = 0;
                    }
                }
            }
            if ((int)receivedMapVersion < 0xa3) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    for (int enemySlot = 0; enemySlot < DAT_GameState::instance.playerDataArray[playerID].enemies;
                        enemySlot++) {
                        DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList[playerID][enemySlot]
                            = DAT_UnitsState::instance
                                  .units[DAT_GameState::instance.playerDataArray[playerID].enemyIDArray[enemySlot]]
                                  .uid;
                    }
                }
            }
            if ((int)receivedMapVersion < 0xa4) {
                this->mapAndTime.dayTicks = 100;
                this->mapAndTime.weekTicks = 100;
                this->mapAndTime.monthTicks = 100;
            }
            if ((int)receivedMapVersion < 0xa6) {
                this->mapAndTime.skirmishNoCowThrowing = 0;
                this->mapAndTime.skirmishNoDogs = 0;
                this->mapAndTime.skirmishNoRushTicks = 0;
                this->mapAndTime.skirmishNoRushTicksLeft = 0;
            }
            if ((int)receivedMapVersion < 0xa8) {
                for (int playerID = 0; playerID < 9; playerID++) {
                    for (int assemblyPoint = 0; assemblyPoint < 7; assemblyPoint++) {
                        DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[assemblyPoint][0] = 0;
                        DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[assemblyPoint][1] = 0;
                    }
                    for (int assemblyPoint = 0; assemblyPoint < 5; assemblyPoint++) {
                        DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[assemblyPoint].x
                            = 0;
                        DAT_GameState::instance.playerDataArray[playerID].specialBuildingAssemblyPoints[assemblyPoint].y
                            = 0;
                    }
                }
            }
        }
    }

}
}
