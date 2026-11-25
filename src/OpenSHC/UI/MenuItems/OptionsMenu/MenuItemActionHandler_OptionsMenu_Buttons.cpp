#include "../OptionsMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00496B80
        void OptionsMenu::MenuItemActionHandler_OptionsMenu_Buttons(int button, ...)
        {
            switch (button) {
            case 39:
                // "Briefing", for campaign missions and for scenarios with a mission type
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL
                    && (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                            && DAT_MapPropertiesState::instance.scenarionMissionType != 0))) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                    DAT_GameCore::instance.gameSuspended = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                }
                break;
            case 10:
                // "Resume Game"
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                break;
            case 2:
                // "Load": always from the main menu; in a game only when playing alone
                if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAIN_MENU) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerDeathRelated
                            != 0) {
                            break;
                        }
                    } else if (DAT_GameSynchronyState::instance.currentGameMode
                        != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        break;
                    }
                    if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT
                        || DAT_GameCore::instance.field_0x6c != 0
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                        break;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(
                    OpenSHC::UI::Enums::MMT_LOAD_MAP);
                break;
            case 3:
                // "Save": alone, or online as the host
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        != 0) {
                        break;
                    }
                } else if (!DAT_GameSynchronyState::instance.isHost) {
                    break;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT
                    || DAT_GameCore::instance.field_0x6c != 0
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(
                    OpenSHC::UI::Enums::MMT_SAVE_MAP);
                break;
            case 26:
                // "Help"
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                // section 0 is help_main.hlp, the help's main page
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::openInGameHelpDialog, DAT_TextEditorState::ptr)(
                    0);
                break;
            case 24:
                // "Options"
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_PAUSE_MENU_OPTIONS);
                break;
            case 7:
                // "Quit Mission": online it opens the online quit dialog; alone it asks as "Exit Crusader" does
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                    && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ONLINE_QUIT_GAME, FALSE);
                    break;
                }
                // falls through
            case 9:
                // "Exit Crusader": the yes/no dialog acts on the button stored here
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GENERAL_QUITGAME);
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = button;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                break;
            case 44:
                // "Restart Mission", for campaign missions, plain scenarios and skirmishes
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                        && DAT_GameCore::instance.field_0x6c == 0)
                    || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = button;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                }
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        }

    }
}
}
