#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b95b74.hpp"
#include "OpenSHC/Globals/INT_00b95f68.hpp"
#include "OpenSHC/Globals/INT_00b960e4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00443070
        void MapEditorProperties::MenuItemActionHandler_MapEditorProperties_MainButtons(int button, ...)
        {
            // nothing while a dialog is open
            if (DAT_MenuTextInputState::instance.currentModalDialog != UI::Enums::MMT_NO_MENU) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_NONE) {
                return;
            }
            DAT_TileMapState::instance.unitPlacementCount = 1;
            switch (button) {
            case 2:
                // load a map
                DAT_MenuTextInputState::instance.field_0x9c = 1;
                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateLoadOrSaveMapUI, DAT_MenuTextInputState::ptr)(
                    UI::Enums::MMT_LOAD_MAP);
                return;
            case 3:
                // save the map; a multiplayer map only once one is loaded in the editor
                if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 0
                    && !DAT_GameCore::instance.mapLoadedForEditor) {
                    return;
                }
                MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::determineScenarioMissionTypeAndResetEvents,
                    DAT_MapPropertiesState::ptr)();
                DAT_MenuTextInputState::instance.field_0x9c = 1;
                DAT_MenuTextInputState::instance.field_0xa4 = 0;
                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateLoadOrSaveMapUI, DAT_MenuTextInputState::ptr)(
                    UI::Enums::MMT_SAVE_MAP);
                INT_00b960e4::instance = TRUE;
                return;
            case 4:
                // new map
                INT_00b960e4::instance = FALSE;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_NEW_MAP_MAPTYPE, 0);
                return;
            case 5:
                // "Main Menu": through the quit dialog once editing has started
                if (INT_00b95f68::instance) {
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 43;
                    MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(UI::Enums::MMT_QUIT_DIALOG);
                    return;
                }
                DAT_GameCore::instance.isTimeHalted2 = 0;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                return;
            case 6:
                // edit the landscape
                if (!DAT_GameCore::instance.mapLoadedForEditor) {
                    return;
                }
                INT_00b95f68::instance = TRUE;
                DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                DAT_GameCore::instance.gameMode_2 = Game::GM_EDITOR;
                DAT_GameCore::instance.missionNumber1to20 = 27;
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                for (int i = 0; i < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++i) {
                    DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] = -1;
                }
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                // the feature tab has a multiplayer version; the one that fits the map is opened
                if (DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.buildMenuTab
                        == Commands::M_MAPPER_SUB_MODE_FEATURE
                    && DAT_GameCore::instance.U2_mapType_singleOrMulti >= 1) {
                    DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.buildMenuTab
                        = Commands::M_MAPPER_SUB_MODE_FEATURE_MP;
                }
                if (DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.buildMenuTab
                        == Commands::M_MAPPER_SUB_MODE_FEATURE_MP
                    && DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                    DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.buildMenuTab
                        = Commands::M_MAPPER_SUB_MODE_FEATURE;
                }
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAP_EDITOR_LANDSCAPING, 0);
                return;
            case 31:
                // play the map: back it up, then start a game from the scenario's settings
                if (!DAT_GameCore::instance.mapLoadedForEditor) {
                    return;
                }
                DAT_GameCore::instance.missionNumber1to20 = 27;
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 32;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_PROGRESS_BAR_BOX, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::renderMenuModal, DAT_MenuModalComposition1::ptr)();
                MACRO_CALL_MEMBER(
                    UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip, DAT_WindowAndDirectDraw::ptr)(0);
                // "auto_backup_map.map"
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    IO::FRT_MAPS, STR_AutoBackupMap);
                FilePackagerObj::instance.loadAndSaveBarFunc = MACRO_CALL(UI::Rendering_Func::RenderLoadAndSaveBar);
                MACRO_CALL_MEMBER(IO::FilePackager_Func::writeMapOrSaveFile, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray);
                if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1] = 1;
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2] = 2;
                }
                DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = OpenSHC::Text::TAIT_NINE__FILTER_B;
                MACRO_CALL_MEMBER(
                    UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                DAT_GameCore::instance.gameMode_2 = Game::GM_BUILDERUnk;
                DAT_GameCore::instance.field_0x6c = 1;
                DAT_GameState::instance.mapAndTime.difficulty = 1;
                DAT_GameCore::instance.section1095 = 0;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
                MACRO_CALL_MEMBER(AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
                ++DAT_TroopValueState::instance.attackInfo.inv_count;
                if (DAT_TroopValueState::instance.attackInfo.inv_count >= 50) {
                    DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                }
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::initializeAttackWaveSlot, DAT_TroopValueState::ptr)(
                    DAT_TroopValueState::instance.attackInfo.inv_count, 1);
                DAT_TroopValueState::instance.attackInfo
                    .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = 2;
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][0]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[0];
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][1]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[1];
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][2]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[3];
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][3]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[2];
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][4]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[4];
                DAT_TroopValueState::instance.attackInfo
                    .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count][8]
                    += DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[5];
                // a loop (with memcpy the compiler reads the next statement's value from the scenario's array)
                for (int i = 0; i < countof(DAT_GameState::instance.mapAndTime.startGoods); ++i) {
                    DAT_GameState::instance.mapAndTime.startGoods[i]
                        = DAT_MapPropertiesState::instance.SEC_StartingResources[i];
                }
                DAT_GameState::instance.mapAndTime.startGoods[Game::Resources::RT_PITCH]
                    = DAT_GameState::instance.mapAndTime.startGoods[Game::Resources::RT_PARTIALPITCH];
                DAT_GameState::instance.mapAndTime.startGoods[Game::Resources::RT_PARTIALPITCH] = 0;
                DAT_GameState::instance.mapAndTime.siegeInformation.archers
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[0];
                DAT_GameState::instance.mapAndTime.siegeInformation.crossbowmen
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[1];
                DAT_GameState::instance.mapAndTime.siegeInformation.spearmen
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[2];
                DAT_GameState::instance.mapAndTime.siegeInformation.pikemen
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[3];
                DAT_GameState::instance.mapAndTime.siegeInformation.macemen
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[4];
                DAT_GameState::instance.mapAndTime.siegeInformation.swordsmen
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[5];
                DAT_GameState::instance.mapAndTime.siegeInformation.knights
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[6];
                DAT_GameState::instance.mapAndTime.siegeInformation.laddermen
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[7];
                DAT_GameState::instance.mapAndTime.siegeInformation.engineers
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[8];
                DAT_GameState::instance.mapAndTime.siegeInformation.monks
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[9];
                DAT_GameState::instance.mapAndTime.siegeInformation.arabianArchers
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[10];
                DAT_GameState::instance.mapAndTime.siegeInformation.slaves
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[11];
                DAT_GameState::instance.mapAndTime.siegeInformation.slingers
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[12];
                DAT_GameState::instance.mapAndTime.siegeInformation.assassins
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[13];
                DAT_GameState::instance.mapAndTime.siegeInformation.horseArchers
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[14];
                DAT_GameState::instance.mapAndTime.siegeInformation.arabianSwordsmen
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[15];
                DAT_GameState::instance.mapAndTime.siegeInformation.fireThrowers
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[16];
                DAT_GameState::instance.mapAndTime.siegeInformation.fireBallistas
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[17];
                DAT_GameState::instance.mapAndTime.siegeInformation.field_0x48
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[18];
                DAT_GameState::instance.mapAndTime.siegeInformation.field_0x4c
                    = DAT_MapPropertiesState::instance.SEC_SiegeInformation[19];
                DAT_GameState::instance.mapAndTime.startingPopularity
                    = DAT_MapPropertiesState::instance.SEC_StartingPopularity * 10;
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::setMonthAndYear, DAT_GameState::ptr)(
                    DAT_MapPropertiesState::instance.SEC_StartingMonth,
                    DAT_MapPropertiesState::instance.SEC_StartingYear);
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::clearEnemyRelatedStructures, DAT_GameState::ptr)();
                // in front of the recruitable loop (behind it the loop's copies take other registers)
                DAT_GameCore::instance.xbowProducible_logic = DAT_MapPropertiesState::instance.SEC_XbowProducible_save;
                DAT_GameCore::instance.bowProducible_logic = DAT_MapPropertiesState::instance.SEC_BowProducible_save;
                DAT_GameCore::instance.pikeProducible_logic = DAT_MapPropertiesState::instance.SEC_PikeProducible_save;
                DAT_GameCore::instance.spearProducible_logic
                    = DAT_MapPropertiesState::instance.SEC_SpearProducible_save;
                DAT_GameCore::instance.swordProducible_logic
                    = DAT_MapPropertiesState::instance.SEC_SwordProducible_save;
                DAT_GameCore::instance.maceProducible_logic = DAT_MapPropertiesState::instance.SEC_MaceProducible_save;
                // cleared in front of the loop (behind it the first four copies' stores move in front of these)
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 0;
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 0;
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 0;
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 0;
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4 = 0;
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 0;
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 0;
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 0;
                DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 0;
                // one loop for both (a loop each changes the registers)
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
                DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
                MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::importTradingCosts, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_CASTLE;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
                return;
            case 9:
                // the description's "Edit"
                MACRO_CALL(MapEditorProperties_Func::MenuItemActionHandler_MapEditorProperties_MapDescriptionBox)(0);
                return;
            case 25:
                // "Edit Scenario": only for a single-player map loaded in the editor
                if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 1
                    || !DAT_GameCore::instance.mapLoadedForEditor) {
                    return;
                }
                INT_00b95f68::instance = TRUE;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_EDIT_SCENARIO, 0);
                return;
            case -1:
                // the description's up arrow
                DAT_00b960f4::instance -= 14;
                if (DAT_00b960f4::instance < 0) {
                    DAT_00b960f4::instance = 0;
                }
                return;
            case -2: {
                // the description's down arrow
                int const limit = INT_00b95b74::instance - 231;
                if (DAT_00b960f4::instance >= limit) {
                    return;
                }
                DAT_00b960f4::instance += 14;
                if (DAT_00b960f4::instance > limit) {
                    DAT_00b960f4::instance = limit;
                }
                return;
            }
            case -3:
                // a multiplayer map's pair for mapU4Int3_balanced: -3 clears it, -4 sets it
                DAT_GameCore::instance.mapU4Int3_balanced = 0;
                return;
            case -4:
                DAT_GameCore::instance.mapU4Int3_balanced = 1;
                return;
            case -5:
                // a single-player invasion map's pair for mapU3EndInt: -5 clears it, -6 sets it
                DAT_GameCore::instance.mapU3EndInt = 0;
                return;
            case -6:
                DAT_GameCore::instance.mapU3EndInt = 1;
                return;
            }
        }

    }
}
}
