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
                /*
                  two entries per pass, exactly as the original binary does
                 */
                for (int buildingType = 0; buildingType < 100; buildingType += 2) {
                    DAT_MapPropertiesState::instance.buildingAvailability[buildingType] = 1;
                    DAT_MapPropertiesState::instance.buildingAvailability[buildingType + 1] = 1;
                }
            }
            if ((int)receivedMapVersion < 0x82) {
                this->mapAndTime.populationIndex = 0;
                this->mapAndTime.lionLocationsXY[0].x = 0;
                this->mapAndTime.lionLocationsXY[0].y = 0;
                this->mapAndTime.lionLocationsXY[1].x = 0;
                this->mapAndTime.lionLocationsXY[1].y = 0;
                this->mapAndTime.lionLocationsXY[2].x = 0;
                this->mapAndTime.lionLocationsXY[2].y = 0;
                this->mapAndTime.lionLocationsXY[3].x = 0;
                this->mapAndTime.lionLocationsXY[3].y = 0;
                this->mapAndTime.field2269_0xdee = 0;
                this->mapAndTime.unitLadyRelated = 0;
                this->mapAndTime.unitJesterRelated = 0;
            }
            if ((int)receivedMapVersion < 0x85) {
                for (int unitID = 1; unitID < 2500; unitID++) {
                    if ((DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE)
                        && (DAT_UnitsState::instance.units[unitID].unitType != ((UnitType)0))) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignNameToUnit, DAT_UnitsState::ptr)(
                            unitID);
                    }
                }
                this->mapAndTime.field3092_0x2654 = 0;
                this->mapAndTime.field3093_0x2658 = 0;
                this->mapAndTime.field3094_0x265c = 0;
                this->mapAndTime.field3095_0x2660 = 0;
                this->mapAndTime.field3096_0x2664 = 0;
                this->mapAndTime.field3097_0x2668 = 0;
                this->mapAndTime.field3098_0x266c = 0;
                this->mapAndTime.field3099_0x2670 = 0;
                this->mapAndTime.field3100_0x2674 = 0;
                this->mapAndTime.field3101_0x2678 = 0;
                this->mapAndTime.field3102_0x267c = 0;
                this->mapAndTime.field3103_0x2680 = 0;
                this->mapAndTime.field3104_0x2684 = 0;
                this->mapAndTime.field3105_0x2688 = 0;
                this->mapAndTime.field3106_0x268c = 0;
                this->mapAndTime.field3107_0x2690 = 0;
                this->mapAndTime.field3108_0x2694 = 0;
                this->mapAndTime.field3109_0x2698 = 0;
                this->mapAndTime.field3110_0x269c = 0;
                this->mapAndTime.field3111_0x26a0 = 0;
                this->mapAndTime.field3112_0x26a4 = 0;
                this->mapAndTime.field3113_0x26a8 = 0;
                this->mapAndTime.field3114_0x26ac = 0;
                this->mapAndTime.field3115_0x26b0 = 0;
                this->mapAndTime.field3116_0x26b4 = 0;
                this->mapAndTime.field3117_0x26b8 = 0;
                this->mapAndTime.field3118_0x26bc = 0;
                this->mapAndTime.field3119_0x26c0 = 0;
                this->mapAndTime.field3120_0x26c4 = 0;
                this->mapAndTime.field3121_0x26c8 = 0;
                this->mapAndTime.field3122_0x26cc = 0;
                this->mapAndTime.field3123_0x26d0 = 0;
            }
            if ((int)receivedMapVersion < 0x87) {
                this->mapAndTime.field2_0x8 = 0;
                this->mapAndTime.field12_0x30 = 0;
                this->mapAndTime.field22_0x58[0][0] = -1;
                this->mapAndTime.field23_0x80 = -1;
                this->mapAndTime.field3_0xc = 0;
                this->mapAndTime.field13_0x34 = 0;
                this->mapAndTime.field22_0x58[0][1] = -1;
                this->mapAndTime.field24_0x84 = -1;
                this->mapAndTime.field4_0x10 = 0;
                this->mapAndTime.field14_0x38 = 0;
                this->mapAndTime.field22_0x58[0][2] = -1;
                this->mapAndTime.field25_0x88 = -1;
                this->mapAndTime.field5_0x14 = 0;
                this->mapAndTime.field15_0x3c = 0;
                this->mapAndTime.field22_0x58[0][3] = -1;
                this->mapAndTime.field26_0x8c = -1;
                this->mapAndTime.field6_0x18 = 0;
                this->mapAndTime.field16_0x40 = 0;
                this->mapAndTime.field22_0x58[0][4] = -1;
                this->mapAndTime.field27_0x90 = -1;
                this->mapAndTime.field7_0x1c = 0;
                this->mapAndTime.field17_0x44 = 0;
                this->mapAndTime.field22_0x58[1][0] = -1;
                this->mapAndTime.field28_0x94 = -1;
                this->mapAndTime.field8_0x20 = 0;
                this->mapAndTime.field18_0x48 = 0;
                this->mapAndTime.field22_0x58[1][1] = -1;
                this->mapAndTime.field29_0x98 = -1;
                this->mapAndTime.field9_0x24 = 0;
                this->mapAndTime.field19_0x4c = 0;
                this->mapAndTime.field22_0x58[1][2] = -1;
                this->mapAndTime.field30_0x9c = -1;
                this->mapAndTime.field10_0x28 = 0;
                this->mapAndTime.field20_0x50 = 0;
                this->mapAndTime.field22_0x58[1][3] = -1;
                this->mapAndTime.field31_0xa0 = -1;
                this->mapAndTime.field11_0x2c = 0;
                this->mapAndTime.field21_0x54 = 0;
                this->mapAndTime.field22_0x58[1][4] = -1;
                this->mapAndTime.field32_0xa4 = -1;
            }
            if ((int)receivedMapVersion < 0x88) {
                this->mapAndTime.gameEventRelatedCountdown = 0;
                this->mapAndTime.unk_signpostDistance = 30;
            }
            if ((int)receivedMapVersion < 0x8a) {
                this->playerDataArray[1].aiControlStatusRelated = -1000;
                this->playerDataArray[2].aiControlStatusRelated = -1000;
                this->playerDataArray[3].aiControlStatusRelated = -1000;
                this->playerDataArray[4].aiControlStatusRelated = -1000;
                this->playerDataArray[5].aiControlStatusRelated = -1000;
                this->playerDataArray[6].aiControlStatusRelated = -1000;
                this->playerDataArray[7].aiControlStatusRelated = -1000;
                this->playerDataArray[8].aiControlStatusRelated = -1000;
            }
            if ((int)receivedMapVersion < 0x8b) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    int cowCount = 0;
                    this->playerDataArray[playerID].counter = 0;
                    int siegeEngineCount = 0;
                    /*
                      three units are handled per pass, exactly as the original binary does
                     */
                    for (int unitID = 1; unitID < 2500; unitID += 3) {
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
                        if ((DAT_UnitsState::instance.units[unitID + 1].logicalState
                                != OpenSHC::Map::Units::ULS_INVISIBLE)
                            && (DAT_UnitsState::instance.units[unitID + 1].unitType != ((UnitType)0))
                            && (DAT_UnitsState::instance.units[unitID + 1].owner == playerID)) {
                            if (DAT_UnitsState::instance.units[unitID + 1].unitType == OpenSHC::Map::Units::UT_COW) {
                                cowCount = cowCount + 1;
                            }
                            if ((DAT_UnitsState::instance.units[unitID + 1].unitType
                                    == OpenSHC::Map::Units::UT_S_CATAPULT)
                                || (DAT_UnitsState::instance.units[unitID + 1].unitType
                                    == OpenSHC::Map::Units::UT_S_TREBUCHET)) {
                                siegeEngineCount = siegeEngineCount + 1;
                            }
                        }
                        if ((DAT_UnitsState::instance.units[unitID + 2].logicalState
                                != OpenSHC::Map::Units::ULS_INVISIBLE)
                            && (DAT_UnitsState::instance.units[unitID + 2].unitType != ((UnitType)0))
                            && (DAT_UnitsState::instance.units[unitID + 2].owner == playerID)) {
                            if (DAT_UnitsState::instance.units[unitID + 2].unitType == OpenSHC::Map::Units::UT_COW) {
                                cowCount = cowCount + 1;
                            }
                            if ((DAT_UnitsState::instance.units[unitID + 2].unitType
                                    == OpenSHC::Map::Units::UT_S_CATAPULT)
                                || (DAT_UnitsState::instance.units[unitID + 2].unitType
                                    == OpenSHC::Map::Units::UT_S_TREBUCHET)) {
                                siegeEngineCount = siegeEngineCount + 1;
                            }
                        }
                    }
                    if (this->playerDataArray[playerID].keep.id == 0) {
                        this->playerDataArray[playerID].counter = siegeEngineCount;
                    } else {
                        this->playerDataArray[playerID].counter = cowCount;
                    }
                }
            }
            short unitJesterRelated = this->mapAndTime.unitJesterRelated;
            short unitLadyRelated = this->mapAndTime.unitLadyRelated;
            if ((int)receivedMapVersion < 141) {
                this->mapAndTime.field2_0x8 = this->mapAndTime.field3124_0x26d4;
                this->mapAndTime.field12_0x30 = this->mapAndTime.field3134_0x26fc;
                this->mapAndTime.field22_0x58[0][0] = this->mapAndTime.field3144_0x2724;
                this->mapAndTime.field23_0x80 = this->mapAndTime.field3154_0x274c;
                this->mapAndTime.field3_0xc = this->mapAndTime.field3125_0x26d8;
                this->mapAndTime.field13_0x34 = this->mapAndTime.field3135_0x2700;
                this->mapAndTime.field22_0x58[0][1] = this->mapAndTime.field3145_0x2728;
                this->mapAndTime.field24_0x84 = this->mapAndTime.field3155_0x2750;
                this->mapAndTime.field4_0x10 = this->mapAndTime.field3126_0x26dc;
                this->mapAndTime.field14_0x38 = this->mapAndTime.field3136_0x2704;
                this->mapAndTime.field22_0x58[0][2] = this->mapAndTime.field3146_0x272c;
                this->mapAndTime.field25_0x88 = this->mapAndTime.field3156_0x2754;
                this->mapAndTime.field5_0x14 = this->mapAndTime.field3127_0x26e0;
                this->mapAndTime.field15_0x3c = this->mapAndTime.field3137_0x2708;
                this->mapAndTime.field22_0x58[0][3] = this->mapAndTime.field3147_0x2730;
                this->mapAndTime.field26_0x8c = this->mapAndTime.field3157_0x2758;
                this->mapAndTime.field6_0x18 = this->mapAndTime.field3128_0x26e4;
                this->mapAndTime.field16_0x40 = this->mapAndTime.field3138_0x270c;
                this->mapAndTime.field22_0x58[0][4] = this->mapAndTime.field3148_0x2734;
                this->mapAndTime.field27_0x90 = this->mapAndTime.field3158_0x275c;
                this->mapAndTime.field7_0x1c = this->mapAndTime.field3129_0x26e8;
                this->mapAndTime.field17_0x44 = this->mapAndTime.field3139_0x2710;
                this->mapAndTime.field22_0x58[1][0] = this->mapAndTime.field3149_0x2738;
                this->mapAndTime.field28_0x94 = this->mapAndTime.field3159_0x2760;
                this->mapAndTime.field8_0x20 = this->mapAndTime.field3130_0x26ec;
                this->mapAndTime.field18_0x48 = this->mapAndTime.field3140_0x2714;
                this->mapAndTime.field22_0x58[1][1] = this->mapAndTime.field3150_0x273c;
                this->mapAndTime.field29_0x98 = this->mapAndTime.field3160_0x2764;
                this->mapAndTime.field9_0x24 = this->mapAndTime.field3131_0x26f0;
                this->mapAndTime.field19_0x4c = this->mapAndTime.field3141_0x2718;
                this->mapAndTime.field22_0x58[1][2] = this->mapAndTime.field3151_0x2740;
                this->mapAndTime.field30_0x9c = this->mapAndTime.field3161_0x2768;
                this->mapAndTime.field10_0x28 = this->mapAndTime.field3132_0x26f4;
                this->mapAndTime.field20_0x50 = this->mapAndTime.field3142_0x271c;
                this->mapAndTime.field22_0x58[1][3] = this->mapAndTime.field3152_0x2744;
                this->mapAndTime.field31_0xa0 = this->mapAndTime.field3162_0x276c;
                this->mapAndTime.field11_0x2c = this->mapAndTime.field3133_0x26f8;
                this->mapAndTime.field21_0x54 = this->mapAndTime.field3143_0x2720;
                this->mapAndTime.field22_0x58[1][4] = this->mapAndTime.field3153_0x2748;
                this->mapAndTime.field32_0xa4 = this->mapAndTime.field3163_0x2770;
            }
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
                    this->playerDataArray[playerID].isFoodTypeBanned[0] = 0;
                    this->playerDataArray[playerID].isFoodTypeBanned[1] = 0;
                    this->playerDataArray[playerID].isFoodTypeBanned[2] = 0;
                    this->playerDataArray[playerID].isFoodTypeBanned[3] = 0;
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
                this->playerDataArray[0].sumOfTotalEnemyUnitsCount = this->playerDataArray[0].enemies;
                this->playerDataArray[1].sumOfTotalEnemyUnitsCount = this->playerDataArray[1].enemies;
                this->playerDataArray[2].sumOfTotalEnemyUnitsCount = this->playerDataArray[2].enemies;
                this->playerDataArray[3].sumOfTotalEnemyUnitsCount = this->playerDataArray[3].enemies;
                this->playerDataArray[4].sumOfTotalEnemyUnitsCount = this->playerDataArray[4].enemies;
                this->playerDataArray[5].sumOfTotalEnemyUnitsCount = this->playerDataArray[5].enemies;
                this->playerDataArray[6].sumOfTotalEnemyUnitsCount = this->playerDataArray[6].enemies;
                this->playerDataArray[7].sumOfTotalEnemyUnitsCount = this->playerDataArray[7].enemies;
                this->playerDataArray[8].sumOfTotalEnemyUnitsCount = this->playerDataArray[8].enemies;
                this->mapAndTime.skirmishStrongWalls = 0;
                this->mapAndTime.skirmishAlliances = 0;
            }
            if ((int)receivedMapVersion < 0x9e) {
                for (int playerID = 0; playerID < 9; playerID++) {
                    for (int assemblyPoint = 0; assemblyPoint < 7; assemblyPoint++) {
                        this->playerDataArray[playerID].barracksAssemblyPoints[assemblyPoint].x = 0;
                        this->playerDataArray[playerID].barracksAssemblyPoints[assemblyPoint].y = 0;
                    }
                }
            }
            if ((int)receivedMapVersion < 0xa2) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    this->mapAndTime.playerBuildingInfoIndex[playerID] = 0;
                    for (int buildingSlot = 0; buildingSlot < 2000; buildingSlot++) {
                        this->mapAndTime.playerEnemyBuildingIDs[playerID][buildingSlot] = 0;
                    }
                }
            }
            if ((int)receivedMapVersion < 0xa3) {
                for (int playerID = 1; playerID < 9; playerID++) {
                    for (int enemySlot = 0; enemySlot < this->playerDataArray[playerID].enemies; enemySlot++) {
                        this->mapAndTime.playerEnemenyUnitUIDShortList[playerID][enemySlot]
                            = DAT_UnitsState::instance.units[this->playerDataArray[playerID].enemyIDArray[enemySlot]]
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
                        this->playerDataArray[playerID].mercenaryAssemblyPoints[assemblyPoint][0] = 0;
                        this->playerDataArray[playerID].mercenaryAssemblyPoints[assemblyPoint][1] = 0;
                    }
                    /*
                      five entries; the generated header splits this array into engineersAssemblyPoints,
                      tunnelersGuildAssemblyPointX/Y, cathedralAssemblyPointX/Y and padding_0x39b4
                     */
                    for (int assemblyPoint = 0; assemblyPoint < 5; assemblyPoint++) {
                        (&this->playerDataArray[playerID].engineersAssemblyPoints[0])[assemblyPoint].x = 0;
                        (&this->playerDataArray[playerID].engineersAssemblyPoints[0])[assemblyPoint].y = 0;
                    }
                }
            }
        }
    }

}
}
