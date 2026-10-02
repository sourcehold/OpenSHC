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
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00444B80
        void InGameMenu::MenuItemActionHandler_InGameMenu_MainButtons(int param_1, ...)
        {
            int iVar1;
            BOOLEnum BVar2;
            MenuViewType menuID;
            if ((param_1 == -1) || (param_1 == -6)) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE, 0);
                }
                if (((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)
                        || ((DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            && (DAT_GameCore::instance.activeMenuTab.tabType
                                != OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))))
                    && (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_PAUSE_MENU);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        ((SoundEffectID)0x101));
                }
            } else if (param_1 == -2) {
                if (((((DAT_GameSynchronyState::instance.syncStatus == 0)
                          && (DAT_GameSynchronyState::instance.saveRelated == 0))
                         && (DAT_GameCore::instance.gamePausedLogical == 0))
                        && ((DAT_GameCore::instance.currentMenuViewType
                                != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                            || ((DAT_GameCore::instance.activeMenuTab.tabType
                                    != OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                                && (DAT_GameCore::instance.activeMenuTab.tabType
                                    != OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))))))
                    && ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .lordKilledByPlayerID
                            == 0
                        && (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            == 0)))) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::confirmAndQueueDestructionCommand,
                        DAT_WallAndPitchState::ptr)();
                }
            } else if (param_1 == -3) {
                if ((((((DAT_GameSynchronyState::instance.syncStatus == 0)
                           && (DAT_GameSynchronyState::instance.saveRelated == 0))
                          && (DAT_GameCore::instance.gamePausedLogical == 0))
                         && ((DAT_GameCore::instance.currentMenuViewType
                                 != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                             || ((DAT_GameCore::instance.activeMenuTab.tabType
                                     != OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                                 && (DAT_GameCore::instance.activeMenuTab.tabType
                                     != OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))))))
                        && (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .lordKilledByPlayerID
                            == 0))
                    && ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            == 0
                        || ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            && (DAT_GameState::instance.mapAndTime.gameOver
                                == DAT_GameSynchronyState::instance.currentPlayerSlotID)))))) {
                    MACRO_CALL(
                        OpenSHC::UI::MenuItems::General_Func::MenuItemActionHandler_General_ToolbarButtonPressed)(
                        OpenSHC::Commands::M_MAPPER_DELETE);
                }
            } else if (param_1 == -5) {
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .playerDeathRelated
                    == 0) {
                    DAT_GameCore::instance.field22_0x64 = 1;
                    DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSpeechStreamsAndResetLoopFlags,
                        DAT_SoundSystemState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                        DAT_BinkControlState::ptr)(1);
                    DAT_GameCore::instance.isBinkVideoPlaying = 0;
                    if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                        && (DAT_GameCore::instance.isSkirmishTrail == TRUE)) {
                        menuID = OpenSHC::UI::Enums::MVT_CRUSADE_MISSION_INTRO;
                    } else {
                        menuID = OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(menuID, 0);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                }
            } else {
                if (param_1 == -4) {
                    DAT_StopHandlingMenuItems::instance = 0;
                }
                if (param_1 == -90) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
                    if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                        /*
                          "Your allies"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "Genie_11.wav");
                    }
                } else {
                    if (param_1 == -0x5b) {
                        DAT_GreatestLordDefinedData::instance.tableSortBy = -1;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_GREATEST_LORD, FALSE);
                    }
                    if (param_1 < -9) {
                        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                            if (-100 < param_1) {
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[0] = -1;
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = -1;
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] = -1;
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] = -1;
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] = -1;
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] = -1;
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] = -1;
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] = -1;
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] = -1;
                                *(undefined4*)((int)DAT_GameSynchronyState::ptr + (-9 - param_1) * 4 + 0x6a8) = 1;
                                DAT_GameSynchronyState::instance.currentPlayerSlotID = -9 - param_1;
                            }
                            if (param_1 != -100) {
                                if (param_1 == -0x65) {
                                    DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                                    DAT_TileMapState::instance.field101_0x5548dc
                                        = DAT_TileMapState::instance.editorActiveBrush;
                                    MACRO_CALL(OpenSHC::UI::MenuItems::MapEditorLandscaping_Func::
                                            MenuItemActionHandler_MapEditorLandscaping_GeneralButtons)(
                                        OpenSHC::Commands::M_MAPPER_TOMAIN);
                                }
                                if (param_1 == -0x66) {
                                    DAT_TileMapState::instance.editorActiveBrush
                                        = DAT_TileMapState::instance.field101_0x5548dc;
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
                        }
                    } else if (param_1 - 0x47U < 9) {
                        if ((DAT_GameSynchronyState::instance.syncStatus == 0)
                            && (DAT_GameCore::instance.gamePausedLogical == 0)) {
                            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                                DAT_StopHandlingMenuItems::instance = 0;
                            }
                            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                                DAT_StopHandlingMenuItems::instance = 0;
                            }
                            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                                == OpenSHC::UI::Enums::MMT_BUILDING_HELP_TEXT) {
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu,
                                    DAT_TextEditorState::ptr)();
                            }
                            if ((((((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
                                       || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL))
                                      && (DAT_GameSynchronyState::instance.currentPlayerSlotID == 2))
                                     || (((DAT_GameSynchronyState::instance.currentPlayerSlotID == TRUE
                                              && (iVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::
                                                                                singlePlayerHasKeepAndGranaryCheck,
                                                      DAT_GameState::ptr)(),
                                                  iVar1 == 0))
                                         && (iVar1
                                             = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getArmySize,
                                                 DAT_UnitsState::ptr)(
                                                 DAT_GameSynchronyState::instance.currentPlayerSlotID),
                                             iVar1 != 0))))
                                    || ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                                        && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1
                                            == OpenSHC::Map::MT_SIEGE))))
                                && (BVar2
                                    = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                                        OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO),
                                    BVar2 == FALSE)) {
                                param_1 = 0x4c;
                            }
                            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                            if (0 < DAT_UnitsState::instance
                                    .unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                    = DAT_GameCore::instance.tabTypeSiegeSubset;
                                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                            }
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                            DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = param_1;
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
                            DAT_BuildingsState::instance.newSelectedBuildingID = 0;
                            DAT_BuildingsState::instance.newSelectedUnitID = 0;
                            if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)
                                && (param_1 == 0x47)) {
                                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(
                                    0xe, OpenSHC::Map::Buildings::BT_HOVEL);
                            }
                        }
                    } else if ((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILD_MENU)
                        || (param_1 != DAT_GameCore::instance.activeMenuTab.tabType)) {
                        DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                        if (0 < DAT_UnitsState::instance
                                .unitCountOfSelection[DAT_GameSynchronyState::instance.currentPlayerSlotID]) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                = DAT_GameCore::instance.tabTypeSiegeSubset;
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = param_1;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
                        switch (param_1) {
                        case 10:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                ((SoundEffectID)0x7b));
                            return;
                        case 0x14:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_SIEGE_EQUIPMENT_DESTROYED
                                    | OpenSHC::Audio::SFX::SEID_INN));
                            return;
                        case 0x19:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_SIEGE_EQUIPMENT_DESTROYED
                                    | OpenSHC::Audio::SFX::SEID_QUARRY_STONE_LIFT_01));
                            return;
                        case 0x1c:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                ((SoundEffectID)0x80));
                            return;
                        case 0x1e:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_SIEGE_EQUIPMENT_DESTROYED
                                    | OpenSHC::Audio::SFX::SEID_QUARRY_STONE_CHIP));
                            return;
                        case 0x28:
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_SIEGE_EQUIPMENT_DESTROYED
                                    | OpenSHC::Audio::SFX::SEID_QUARRY_STONE_BREAK));
                        }
                    }
                }
            }
        }

    }
}
}
