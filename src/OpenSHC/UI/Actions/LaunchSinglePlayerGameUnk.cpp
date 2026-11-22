// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../Actions.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"

namespace OpenSHC {
namespace UI {

    // Starts a single-player game on the map picked in the map choice, or on the one standaloneFilename already names.
    // FUNCTION: STRONGHOLDCRUSADER 0x0042C620
    void Actions::LaunchSinglePlayerGameUnk(int useStandaloneFilename)
    {
        // the map's file name: a map name (1001 bytes, as standaloneFilename) and ".map"; and a copy of the name
        char mapFileName[1005];
        char mapName[1001];

        int const playerSlot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        DAT_GameCore::instance.section1066 = 1;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
        DAT_GameSynchronyState::instance.currentPlayerSlotID = playerSlot;
        // set before the map is loaded (in this order: in ascending order two of the stores move)
        DAT_MapPropertiesState::instance.SEC_XbowProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_PikeProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_SwordProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_BowProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_SpearProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_MaceProducible_save = 1;
        for (int i = 0; i < countof(DAT_MapPropertiesState::instance.SEC_MercRecruitable); ++i) {
            DAT_MapPropertiesState::instance.barracksRecruitability.array.barracksRecruitability[i] = 1;
            DAT_MapPropertiesState::instance.SEC_MercRecruitable[i] = 1;
        }
        if (!useStandaloneFilename) {
            // the selection is read first (scroll offset + selection swaps the two loads)
            strcpy(mapFileName,
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                            + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset]));
            // ".map"
            strcat(mapFileName, s__map_005a2294);
        } else {
            strcpy(mapFileName, DAT_GameCore::instance.standaloneFilename);
            // ".map"
            strcat(mapFileName, s__map_005a2294);
            // kept for behind the load, where it is written back to standaloneFilename
            strcpy(mapName, DAT_GameCore::instance.standaloneFilename);
        }
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::loadMap, DAT_MapPropertiesState::ptr)(mapFileName);
        DAT_GameCore::instance.selectedLordType_2Unk = DAT_GameCore::instance.selectedLordTypeUnk;
        // set again behind the loaded map's settings, with the game's own copies: every weapon can be made
        DAT_MapPropertiesState::instance.SEC_XbowProducible_save = 1;
        DAT_GameCore::instance.xbowProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_BowProducible_save = 1;
        DAT_GameCore::instance.bowProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_PikeProducible_save = 1;
        DAT_GameCore::instance.pikeProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_SpearProducible_save = 1;
        DAT_GameCore::instance.spearProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_SwordProducible_save = 1;
        DAT_GameCore::instance.swordProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_MaceProducible_save = 1;
        DAT_GameCore::instance.maceProducible_logic = 1;
        // The mission type picked in the map choice: 0 just build, 1 economic, 2 siege, 3 invasion.
        // The difficulty is remembered for each.
        switch (DAT_MapMissionType::instance) {
        case 0:
            DAT_GameCore::instance.missionDifficulty_0 = DAT_GameState::instance.mapAndTime.difficulty;
            break;
        case 1:
            DAT_GameCore::instance.missionDifficulty_1 = DAT_GameState::instance.mapAndTime.difficulty;
            break;
        case 2:
            DAT_GameCore::instance.missionDifficulty_2 = DAT_GameState::instance.mapAndTime.difficulty;
            break;
        case 3:
            DAT_GameCore::instance.missionDifficulty_3 = DAT_GameState::instance.mapAndTime.difficulty;
            break;
        }
        if (DAT_MapMissionType::instance == 2) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::createChainedMissionOutcomeEvents,
                DAT_MapPropertiesState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
        }
        // cleared in front of the loop (behind it the loop's copies take the register that holds the zero)
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4 = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 0;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 0;
        for (int i = 0; i < countof(DAT_GameState::instance.mapAndTime.euroRecruitable); ++i) {
            DAT_GameState::instance.mapAndTime.euroRecruitable[i]
                = DAT_MapPropertiesState::instance.barracksRecruitability.array.barracksRecruitability[i];
            DAT_GameState::instance.mapAndTime.mercRecruitable[i]
                = DAT_MapPropertiesState::instance.SEC_MercRecruitable[i];
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[0]) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[1]) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[2]) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[3]) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[4]) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4 = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[5]) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        }
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[6]) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 1;
        }
        if (!useStandaloneFilename) {
            strcpy(DAT_GameCore::instance.standaloneFilename,
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                            + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset]));
        } else {
            strcpy(DAT_GameCore::instance.standaloneFilename, mapName);
        }
        DAT_GameState::instance.mapAndTime.unitJesterRelated = 0;
        DAT_GameState::instance.mapAndTime.unitLadyRelated = 0;
        if (DAT_MapMissionType::instance == 2) {
            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::triggerDeathAnimationForAllWildlife, DAT_UnitsState::ptr)();
            // slots 1 and 2 swap colours when the player takes slot 2
            if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1] = 1;
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2] = 2;
            } else {
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1] = 2;
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2] = 1;
            }
            // the mission type is tested again, as in the original (without it the colours' two arms change)
            if (DAT_MapMissionType::instance == 2 && DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
                // the map's siege engines come as an attack wave, more of them the higher the difficulty
                int percentage = 100;
                switch (DAT_GameState::instance.mapAndTime.difficulty) {
                case 0:
                    percentage = 66;
                    break;
                case 2:
                    percentage = 133;
                    break;
                case 3:
                    percentage = 166;
                    break;
                }
                ++DAT_TroopValueState::instance.attackInfo.inv_count;
                if (DAT_TroopValueState::instance.attackInfo.inv_count
                    >= countof(DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray)) {
                    DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::initializeAttackWaveSlot, DAT_TroopValueState::ptr)(
                    DAT_TroopValueState::instance.attackInfo.inv_count, 1);
                DAT_TroopValueState::instance.attackInfo
                    .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = 4;
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][0]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[0] * percentage / 100;
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][1]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[1] * percentage / 100;
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][2]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[3] * percentage / 100;
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][3]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[2] * percentage / 100;
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][4]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[4] * percentage / 100;
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][8]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[5] * percentage / 100;
            }
        }
        // the siege's twenty troop counts as an array (written out, the zero stores take another register)
        int* const siegeUnits = &DAT_GameState::instance.mapAndTime.siegeInformation.archers;
        if (DAT_SH1_SiegeAdvancedMode::instance) {
            if (DAT_MapMissionType::instance == 2) {
                // the troops as picked in the map choice
                int const* const pickedUnits = &DAT_SiegeInformationArray::instance[0][0];
                for (int i = 0; i < countof(DAT_MapPropertiesState::instance.SEC_SiegeInformation); ++i) {
                    siegeUnits[i] = pickedUnits[i];
                }
                // the tunnelers take the eleventh number too
                DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount = pickedUnits[10];
            }
        } else if (DAT_MapMissionType::instance == 2 && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2) {
            // the player attacks with 70% of the map's troops
            for (int i = 0; i < countof(DAT_MapPropertiesState::instance.SEC_SiegeInformation); ++i) {
                siegeUnits[i] = DAT_MapPropertiesState::instance.SEC_SiegeInformation[i] * 7 / 10;
            }
            DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount
                = DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount * 7 / 10;
        }
        if (DAT_MapMissionType::instance == 3 && DAT_GameState::instance.mapAndTime.difficulty != 0
            && !MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::mapHasCertainEvent, DAT_MapPropertiesState::ptr)()) {
            // The player's own troops are thinned: every nth one goes, until a part of their value is gone.
            // counter is declared first (behind total the two are set to zero in the other order)
            int counter = 0;
            int total = 0;
            int nth = 0;
            for (int unitID = 1; unitID < countof(DAT_UnitsState::instance.units); ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && DAT_UnitsState::instance.units[unitID].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0) {
                    total += MACRO_CALL_MEMBER(
                        Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                        (Map::Units::UnitType)DAT_UnitsState::instance.units[unitID].unitType);
                }
            }
            // total becomes the value that is left to take away
            switch (DAT_GameState::instance.mapAndTime.difficulty) {
            case 1:
                // every fourth unit, until a quarter of the value is gone
                nth = 4;
                total -= total * 3 / 4;
                break;
            case 2:
                // every third, a third
                nth = 3;
                total -= total * 2 / 3;
                break;
            case 3:
                // every second, half
                nth = 2;
                total -= total / 2;
                break;
            }
            for (int pass = 0; pass < 3; ++pass) {
                for (int unitID = 1; unitID < countof(DAT_UnitsState::instance.units); ++unitID) {
                    if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0
                        && DAT_UnitsState::instance.units[unitID].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime != 0) {
                        ++counter;
                        if (counter == nth) {
                            total -= MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                                (Map::Units::UnitType)DAT_UnitsState::instance.units[unitID].unitType);
                            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deleteUnit, DAT_UnitsState::ptr)(unitID);
                            // a tower's engine leaves its tower empty
                            if (DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_S_MANGONEL
                                || DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_S_BALLISTA) {
                                int const building = DAT_TileMapState::instance
                                                         .BuildingLayer[DAT_UnitsState::instance.units[unitID].tile];
                                if (building != 0) {
                                    DAT_BuildingsState::instance.buildings[building].defensiveTowerEngineType = 0;
                                }
                            }
                            if (total <= 0) {
                                // ends the passes too
                                pass = 10;
                                break;
                            }
                            counter = 0;
                        }
                    }
                }
            }
        }
        // Not a siege: no attacking troops. Its own test in front of the siege's (as that test's else arm the blocks
        // above stay in the written order, where the original has them behind the keep's part).
        if (DAT_MapMissionType::instance != 2) {
            for (int i = 0; i < countof(DAT_MapPropertiesState::instance.SEC_SiegeInformation); ++i) {
                siegeUnits[i] = 0;
            }
            DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount = 0;
        }
        if (DAT_MapMissionType::instance == 2) {
            // a siege starts without peasants
            for (int unitID = 1; unitID < countof(DAT_UnitsState::instance.units); ++unitID) {
                if (DAT_UnitsState::instance.units[unitID].logicalState != Map::Units::ULS_INVISIBLE
                    && DAT_UnitsState::instance.units[unitID].unitType == Map::Units::UT_PEASANT) {
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deleteUnit, DAT_UnitsState::ptr)(unitID);
                }
            }
        }
        if (DAT_MapMissionType::instance == 0) {
            // no jester and no lady: each is removed if its unit still has the uid the player's record holds
            DAT_GameState::instance.mapAndTime.unitJesterRelated = 0;
            int const jester
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .jesterIDUnk;
            if (jester != 0
                && DAT_UnitsState::instance.units[jester].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someUnitIDSelfRef_2) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .jesterIDUnk = 0;
                DAT_UnitsState::instance.units[jester].logicalState = Map::Units::ULS_REMOVE;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someUnitIDSelfRef_2 = 0;
            }
            DAT_GameState::instance.mapAndTime.unitLadyRelated = 0;
            int const lady
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .ladyIDUnk;
            if (lady != 0
                && DAT_UnitsState::instance.units[lady].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someUnitIDSelfRef) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].ladyIDUnk
                    = 0;
                DAT_UnitsState::instance.units[lady].logicalState = Map::Units::ULS_REMOVE;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someUnitIDSelfRef = 0;
            }
        }
        if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 2) {
            // slot 2's starting gold is paid out at once
            DAT_GameState::instance.playerDataArray[2].currentResources[Game::Resources::RT_GOLD]
                += DAT_GameState::instance.playerDataArray[2].startResources[Game::Resources::RT_GOLD];
            DAT_GameState::instance.playerDataArray[2].startResources[Game::Resources::RT_GOLD] = 0;
            DAT_GameState::instance.playerDataArray[2].beforeLastMonthsGold
                = (short)DAT_GameState::instance.playerDataArray[2].currentResources[Game::Resources::RT_GOLD];
            DAT_GameState::instance.playerDataArray[2].lastMonthsGold
                = (short)DAT_GameState::instance.playerDataArray[2].currentResources[Game::Resources::RT_GOLD];
        }
        if (DAT_GameCore::instance.mapU4Int1) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentResources[Game::Resources::RT_GOLD] = 600;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .startResources[Game::Resources::RT_GOLD] = 0;
        }
        DAT_GameCore::instance.missionNumber1to20 = 28;
        // the view starts on slot 1's keep, or for another slot on the map's first signpost
        if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
            int const keep = DAT_GameState::instance.playerDataArray[1].buildingEntryInfos[0].id;
            if (keep != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                    DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[keep].x + 2,
                    DAT_BuildingsState::instance.buildings[keep].y + 2);
            }
        } else if (DAT_GameState::instance.mapAndTime.signpostEntryData[0].x != 0
            && DAT_GameState::instance.mapAndTime.signpostEntryData[0].y != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                DAT_ViewportRenderState::ptr)(DAT_GameState::instance.mapAndTime.signpostEntryData[0].x,
                DAT_GameState::instance.mapAndTime.signpostEntryData[0].y);
        }
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, DAT_ViewportRenderState::ptr)();
        if (DAT_GameCore::instance.mapU4Int1) {
            MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::pathfindingUpdate_0x4a8ab0, DAT_PathFindingState::ptr)(30);
        }
        // compared with 1 as in the original (a truth test compares with zero)
        if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_INVASION && useStandaloneFilename != 1) {
            // an invasion shows its description first
            DAT_GameCore::instance.gameSuspended = 0;
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_SCENARIO_DESCRIPTION, 10000);
        } else {
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_CASTLE;
            // a call in each arm (one call with a ? : argument computes the number without a jump)
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_UNKNOWN_49_DOES_NOTHINGUnk) {
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
            } else {
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 10000);
            }
        }
        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
        DWORD_00b95b1c::instance = timeGetTime();
        DAT_00b960dc::instance = 1;
    }

}
}
