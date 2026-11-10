#include "../InGameMenu.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuItems/MapEditorLandscaping.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GreatestLordDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00444B80
        void InGameMenu::MenuItemActionHandler_InGameMenu_MainButtons(int buttonID, ...)
        {
            if (buttonID == -1 || buttonID == -6) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                    return;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE, 0);
                    return;
                }
                if ((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                        || (DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            && DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))
                    && DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_PAUSE_MENU);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0x101);
                }
                return;
            }
            if (buttonID == -2) {
                if (DAT_GameSynchronyState::instance.syncStatus == 0
                    && DAT_GameSynchronyState::instance.saveRelated == 0
                    && DAT_GameCore::instance.gamePausedLogical == 0
                    && (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                        || (DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            && DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))
                    && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordKilledByPlayerID
                        == 0
                    && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::confirmAndQueueDestructionCommand,
                        DAT_WallAndPitchState::ptr)();
                }
            } else if (buttonID == -3) {
                if (DAT_GameSynchronyState::instance.syncStatus == 0
                    && DAT_GameSynchronyState::instance.saveRelated == 0
                    && DAT_GameCore::instance.gamePausedLogical == 0
                    && (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                        || (DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            && DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))
                    && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .lordKilledByPlayerID
                        == 0
                    && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            == 0
                        || (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            && DAT_GameState::instance.mapAndTime.gameOver
                                == DAT_GameSynchronyState::instance.currentPlayerSlotID))) {
                    MACRO_CALL(
                        OpenSHC::UI::MenuItems::General_Func::MenuItemActionHandler_General_ToolbarButtonPressed)(
                        OpenSHC::Commands::M_MAPPER_DELETE);
                }
            } else if (buttonID == -5) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .playerDeathRelated
                    == 0) {
                    DAT_GameCore::instance.gameSuspended = 1;
                    DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                        DAT_SoundSystemState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                        DAT_BinkControlState::ptr)(1);
                    DAT_GameCore::instance.isBinkVideoPlaying = 0;
                    // compared with TRUE: the original tests isSkirmishTrail == 1
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                        && DAT_GameCore::instance.isSkirmishTrail == TRUE) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_CRUSADE_MISSION_INTRO, 0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                }
            } else {
                // nested, with the two early returns: one else-if chain loses the match
                if (buttonID == -4) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    return;
                }
                if (buttonID == -90) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
                    if (DAT_GameCore::instance.genieVoiceActive) {
                        // "Genie_11.wav"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_YourAllies);
                    }
                } else {
                    if (buttonID == -91) {
                        DAT_GreatestLordDefinedData::instance.tableSortBy = -1;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_GREATEST_LORD, FALSE);
                        return;
                    }
                    if (buttonID <= -10) {
                        if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                            return;
                        }
                        if (buttonID > -100) {
                            for (int player = 0;
                                player < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++player) {
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] = -1;
                            }
                            // buttons -10 to -17 pick editor player 1 to 8
                            int const slot = -9 - buttonID;
                            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] = 1;
                            DAT_GameSynchronyState::instance.currentPlayerSlotID = slot;
                            return;
                        }
                        // the -100 test is redundant; without it the code changes
                        if (buttonID != -100) {
                            if (buttonID == -101) {
                                DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                                DAT_TileMapState::instance.savedEditorActiveBrush
                                    = DAT_TileMapState::instance.editorActiveBrush;
                                MACRO_CALL(OpenSHC::UI::MenuItems::MapEditorLandscaping_Func::
                                        MenuItemActionHandler_MapEditorLandscaping_GeneralButtons)(
                                    OpenSHC::Commands::M_MAPPER_TOMAIN);
                            } else if (buttonID == -102) {
                                DAT_TileMapState::instance.editorActiveBrush
                                    = DAT_TileMapState::instance.savedEditorActiveBrush;
                                DAT_UnitsState::instance.lastSelectedUnitID = 0;
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne,
                                    DAT_UnitsState::ptr)();
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs,
                                    DAT_UnitsState::ptr)();
                                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                        MenuItemActionHandler_General_ToolbarButtonPressed)(
                                    OpenSHC::Commands::M_MAPPER_TOTEST);
                            }
                        }
                    } else if (buttonID >= OpenSHC::UI::Enums::BASMTT_STATUS_OVERVIEW
                        && buttonID <= OpenSHC::UI::Enums::BASMTT_STATUS_RELIGION) {
                        if (DAT_GameSynchronyState::instance.syncStatus != 0
                            || DAT_GameCore::instance.gamePausedLogical != 0) {
                            return;
                        }
                        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                            || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                            DAT_StopHandlingMenuItems::instance = 0;
                            return;
                        }
                        if (DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_BUILDING_HELP_TEXT) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                                DAT_TextEditorState::ptr)();
                        }
                        int statusTab = buttonID;
                        if ((((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                                  || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                                 && DAT_GameSynchronyState::instance.currentPlayerSlotID == 2)
                                || (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1
                                    && MACRO_CALL_MEMBER(
                                           OpenSHC::Game::GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck,
                                           DAT_GameState::ptr)()
                                        == 0
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getArmySize,
                                           DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID)
                                        != 0)
                                || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                                    && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE))
                            && !MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO)) {
                            statusTab = OpenSHC::UI::Enums::BASMTT_STATUS_ARMY;
                        }
                        DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                        if (DAT_UnitsState::instance
                                .unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            > 0) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                = DAT_GameCore::instance.tabTypeSiegeSubset;
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                        DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = statusTab;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
                        DAT_BuildingsState::instance.newSelectedBuildingID = 0;
                        DAT_BuildingsState::instance.newSelectedUnitID = 0;
                        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL
                            && statusTab == OpenSHC::UI::Enums::BASMTT_STATUS_OVERVIEW) {
                            // tutorial action 14: the overview tab is open (switchToMenuView on main sets 11, same
                            // building)
                            MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(
                                14, OpenSHC::Map::Buildings::BT_HOVEL);
                        }
                    } else if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILD_MENU
                        || buttonID != DAT_GameCore::instance.activeMenuTab.buildMenuTab) {
                        DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                        if (DAT_UnitsState::instance
                                .unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            > 0) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                = DAT_GameCore::instance.tabTypeSiegeSubset;
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = buttonID;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
                        switch (buttonID) {
                        case OpenSHC::UI::Enums::BMTT_CASTLE:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_UNKNOWN_0x7B);
                            break;
                        case OpenSHC::UI::Enums::BMTT_INDUSTRY:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_UNKNOWN_0x7c);
                            break;
                        case OpenSHC::UI::Enums::BMTT_TOWN:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_UNKNOWN_0x7d);
                            break;
                        case OpenSHC::UI::Enums::BMTT_FARMS:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_UNKNOWN_0x7e);
                            break;
                        case OpenSHC::UI::Enums::BMTT_FOOD:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_UNKNOWN_0x7f);
                            break;
                        case OpenSHC::UI::Enums::BMTT_WEAPONS:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_UNKNOWN_0x80);
                            break;
                        }
                    }
                }
            }
        }

    }
}
}
