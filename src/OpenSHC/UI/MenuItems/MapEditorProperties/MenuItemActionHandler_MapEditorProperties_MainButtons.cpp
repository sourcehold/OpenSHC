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
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
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
        void MapEditorProperties::MenuItemActionHandler_MapEditorProperties_MainButtons(int param_1, ...)
        {
            byte(*pabVar1)[10];
            byte* pbVar2;
            char cVar3;
            char cVar4;
            char cVar5;
            int iVar6;
            int* piVar7;
            int* piVar8;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_NONE)) {
                DAT_TileMapState::instance.unitPlacementCount = 1;
                switch (param_1) {
                case 2:
                    DAT_MenuTextInputState::instance.field_0x9c = 1;
                    MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateLoadOrSaveMapUI,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_LOAD_MAP);
                    return;
                case 3:
                    if ((!DAT_GameCore::instance.U2_mapType_singleOrMulti)
                        || (DAT_GameCore::instance.mapLoadedForEditor)) {
                        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::determineScenarioMissionTypeAndResetEvents,
                            DAT_MapPropertiesState::ptr)();
                        DAT_MenuTextInputState::instance.field_0x9c = 1;
                        DAT_MenuTextInputState::instance.field_0xa4 = 0;
                        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateLoadOrSaveMapUI,
                            DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_SAVE_MAP);
                        INT_00b960e4::instance = 1;
                        return;
                    }
                    break;
                case 4:
                    INT_00b960e4::instance = 0;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_NEW_MAP_MAPTYPE, 0);
                    return;
                case 5:
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
                    if (DAT_GameCore::instance.mapLoadedForEditor) {
                        INT_00b95f68::instance = 1;
                        DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                        DAT_GameCore::instance.gameMode_2 = Game::GM_EDITOR;
                        DAT_GameCore::instance.missionNumber1to20 = 27;
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                        for (int i = 0; i < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++i) {
                            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] = -1;
                        }
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                        if (DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.tabType == 237) {
                            if (DAT_GameCore::instance.U2_mapType_singleOrMulti < 1)
                                goto LAB_00443214;
                            DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.tabType = 239;
                        } else if (DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.tabType != 239)
                            goto LAB_00443214;
                        if (!DAT_GameCore::instance.U2_mapType_singleOrMulti) {
                            DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.tabType = 237;
                        }
                    LAB_00443214:
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_MAP_EDITOR_LANDSCAPING, 0);
                        return;
                    }
                    break;
                case 9:
                    MACRO_CALL(UI::MenuItems::MapEditorProperties_Func::
                            MenuItemActionHandler_MapEditorProperties_MapDescriptionBox)();
                    return;
                case 25:
                    if ((DAT_GameCore::instance.U2_mapType_singleOrMulti != 1)
                        && (DAT_GameCore::instance.mapLoadedForEditor)) {
                        INT_00b95f68::instance = 1;
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_EDIT_SCENARIO, 0);
                        return;
                    }
                    break;
                case 31:
                    if (DAT_GameCore::instance.mapLoadedForEditor) {
                        DAT_GameCore::instance.missionNumber1to20 = 27;
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 32;
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_PROGRESS_BAR_BOX, FALSE);
                        MACRO_CALL_MEMBER(
                            UI::MenuModalComposition_Func::renderMenuModal, DAT_MenuModalComposition1::ptr)();
                        MACRO_CALL_MEMBER(
                            UI::Rendering::WindowAndDirectDraw_Func::renderBltAndFlip, DAT_WindowAndDirectDraw::ptr)(0);
                        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                            IO::FRT_MAPS, STR_AutoBackupMap);
                        FilePackagerObj::instance.loadAndSaveBarFunc
                            = MACRO_CALL(UI::Rendering_Func::RenderLoadAndSaveBar);
                        MACRO_CALL_MEMBER(IO::FilePackager_Func::writeMapOrSaveFile, FilePackagerObj::ptr)(
                            DAT_MapDefinedData::instance.MapSectionAddressArray);
                        if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE) {
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1] = 1;
                            DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2] = 2;
                        }
                        DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = 9;
                        MACRO_CALL_MEMBER(
                            UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                        DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                        DAT_GameCore::instance.gameMode_2 = Game::GM_BUILDERUnk;
                        DAT_GameCore::instance.field_0x6c = 1;
                        DAT_GameState::instance.mapAndTime.difficulty = 1;
                        DAT_GameCore::instance.section1095 = 0;
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
                        MACRO_CALL_MEMBER(AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
                        ++DAT_TroopValueState::instance.attackInfo.inv_count;
                        if (49 < DAT_TroopValueState::instance.attackInfo.inv_count) {
                            DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                        }
                        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
                            DAT_TroopValueState::ptr)(DAT_TroopValueState::instance.attackInfo.inv_count, 1);
                        cVar3 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[0];
                        DAT_TroopValueState::instance.attackInfo
                            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = 2;
                        cVar4 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[1];
                        pabVar1 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                            + DAT_TroopValueState::instance.attackInfo.inv_count;
                        (*pabVar1)[0] = (*pabVar1)[0] + cVar3;
                        cVar5 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[3];
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 1;
                        *pbVar2 += cVar4;
                        cVar3 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[2];
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 2;
                        *pbVar2 += cVar5;
                        cVar4 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[4];
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 3;
                        *pbVar2 += cVar3;
                        cVar3 = (char)DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[5];
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 4;
                        *pbVar2 += cVar4;
                        pbVar2 = DAT_TroopValueState::instance.attackInfo
                                     .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                            + 8;
                        *pbVar2 += cVar3;
                        DAT_GameState::instance.mapAndTime.siegeInformation.archers
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[0];
                        piVar7 = DAT_MapPropertiesState::instance.SEC_StartingResources;
                        piVar8 = DAT_GameState::instance.mapAndTime.startGoods;
                        for (iVar6 = 25; iVar6 != 0; --iVar6) {
                            *piVar8 = *piVar7;
                            ++piVar7;
                            ++piVar8;
                        }
                        DAT_GameState::instance.mapAndTime.startGoods[7]
                            = DAT_GameState::instance.mapAndTime.startGoods[8];
                        DAT_GameState::instance.mapAndTime.siegeInformation.pikemen
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[3];
                        DAT_GameState::instance.mapAndTime.siegeInformation.spearmen
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[2];
                        DAT_GameState::instance.mapAndTime.siegeInformation.crossbowmen
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[1];
                        DAT_GameState::instance.mapAndTime.siegeInformation.knights
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[6];
                        DAT_GameState::instance.mapAndTime.siegeInformation.swordsmen
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[5];
                        DAT_GameState::instance.mapAndTime.siegeInformation.macemen
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[4];
                        DAT_GameState::instance.mapAndTime.siegeInformation.monks
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[9];
                        DAT_GameState::instance.mapAndTime.siegeInformation.engineers
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[8];
                        DAT_GameState::instance.mapAndTime.siegeInformation.laddermen
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[7];
                        DAT_GameState::instance.mapAndTime.siegeInformation.slingers
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[12];
                        DAT_GameState::instance.mapAndTime.siegeInformation.slaves
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[11];
                        DAT_GameState::instance.mapAndTime.siegeInformation.arabianArchers
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[10];
                        DAT_GameState::instance.mapAndTime.siegeInformation.arabianSwordsmen
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[15];
                        DAT_GameState::instance.mapAndTime.siegeInformation.horseArchers
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[14];
                        DAT_GameState::instance.mapAndTime.siegeInformation.assassins
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[13];
                        DAT_GameState::instance.mapAndTime.siegeInformation.field_0x48
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[18];
                        DAT_GameState::instance.mapAndTime.siegeInformation.fireBallistas
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[17];
                        DAT_GameState::instance.mapAndTime.siegeInformation.fireThrowers
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[16];
                        DAT_GameState::instance.mapAndTime.startGoods[8] = 0;
                        DAT_GameState::instance.mapAndTime.siegeInformation.field_0x4c
                            = DAT_MapPropertiesState::instance.SEC_SiegeInformation[19];
                        DAT_GameState::instance.mapAndTime.startingPopularity
                            = DAT_MapPropertiesState::instance.SEC_StartingPopularity * 10;
                        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::setMonthAndYear, DAT_GameState::ptr)(
                            DAT_MapPropertiesState::instance.SEC_StartingMonth,
                            DAT_MapPropertiesState::instance.SEC_StartingYear);
                        MACRO_CALL_MEMBER(
                            Game::GameStateStructures_Func::clearEnemyRelatedStructures, DAT_GameState::ptr)();
                        DAT_GameState::instance.mapAndTime.mercRecruitable[3]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[3];
                        DAT_GameCore::instance.xbowProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_XbowProducible_save;
                        DAT_GameCore::instance.bowProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_BowProducible_save;
                        DAT_GameCore::instance.pikeProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_PikeProducible_save;
                        DAT_GameState::instance.mapAndTime.mercRecruitable[2]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[2];
                        DAT_GameState::instance.mapAndTime.euroRecruitable[4]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.macemen;
                        DAT_GameState::instance.mapAndTime.mercRecruitable[4]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[4];
                        DAT_GameState::instance.mapAndTime.euroRecruitable[5]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.swordsmen;
                        DAT_GameCore::instance.spearProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_SpearProducible_save;
                        DAT_GameState::instance.mapAndTime.mercRecruitable[5]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[5];
                        DAT_GameState::instance.mapAndTime.mercRecruitable[0]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[0];
                        DAT_GameState::instance.mapAndTime.euroRecruitable[6]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.knights;
                        DAT_GameCore::instance.swordProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_SwordProducible_save;
                        DAT_GameCore::instance.maceProducible_logic
                            = (int)DAT_MapPropertiesState::instance.SEC_MaceProducible_save;
                        DAT_GameState::instance.mapAndTime.mercRecruitable[1]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[1];
                        DAT_GameState::instance.mapAndTime.mercRecruitable[6]
                            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[6];
                        DAT_GameState::instance.mapAndTime.euroRecruitable[0]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.archers;
                        DAT_GameState::instance.mapAndTime.euroRecruitable[1]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.crossbowmen;
                        DAT_GameState::instance.mapAndTime.euroRecruitable[2]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.spearmen;
                        DAT_GameState::instance.mapAndTime.euroRecruitable[3]
                            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.pikemen;
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[0] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[2] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0);
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0);
                        if (DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0) {
                            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
                        }
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0);
                        if (DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0) {
                            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
                        }
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0);
                        if (DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0) {
                            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
                            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
                        }
                        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c
                            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0);
                        DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
                        MACRO_CALL_MEMBER(
                            Map::MapPropertiesState_Func::importTradingCosts, DAT_MapPropertiesState::ptr)();
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_HUNTERSHUT;
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_BUILD_MENU, 0);
                        return;
                    }
                    break;
                case -6:
                    DAT_GameCore::instance.mapU3EndInt = 1;
                    break;
                case -5:
                    DAT_GameCore::instance.mapU3EndInt = 0;
                    return;
                case -4:
                    DAT_GameCore::instance.mapU4Int3_balanced = 1;
                    return;
                case -3:
                    DAT_GameCore::instance.mapU4Int3_balanced = 0;
                    return;
                case -2:
                    iVar6 = INT_00b95b74::instance - 231;
                    if ((DAT_00b960f4::instance < iVar6)
                        && (DAT_00b960f4::instance = DAT_00b960f4::instance + 14, iVar6 < DAT_00b960f4::instance)) {
                        DAT_00b960f4::instance = iVar6;
                        return;
                    }
                    break;
                case -1:
                    DAT_00b960f4::instance -= 14;
                    if (DAT_00b960f4::instance < 0) {
                        DAT_00b960f4::instance = 0;
                        return;
                    }
                }
            }
        }

    }
}
}
