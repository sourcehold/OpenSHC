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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::Audio::SFX::SpeechEffectID;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
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
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00496B80
        void OptionsMenu::MenuItemActionHandler_OptionsMenu_Buttons(int param_1, ...)
        {
            bool bVar1;
            MenuModalType dialogID;
            switch (param_1) {
            case 2:
                /*
                  "Load"
                 */
                if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAIN_MENU) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                        bVar1 = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .playerDeathRelated
                            == 0;
                    } else {
                        bVar1 = DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER;
                    }
                    if (((!bVar1) || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR))
                        || ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT
                            || ((DAT_GameCore::instance.field24_0x6c != 0
                                || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL))))))
                        break;
                }
                /*
                  load
                 */
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(9);
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case 3:
                /*
                  "Save"
                 */
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        != 0)
                        break;
                } else if (DAT_GameSynchronyState::instance.isHost == FALSE)
                    break;
                if ((((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                         && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.field24_0x6c == 0))
                    && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL)) {
                    /*
                      save
                     */
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(10);
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
                break;
            case 7:
                /*
                  "Quit mission"
                 */
                if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ONLINE_QUIT_GAME, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
            case 9:
                /*
                  "Exit Crusader"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GENERAL_QUITGAME);
            LAB_00496da8:
                dialogID = OpenSHC::UI::Enums::MMT_YES_NO_DIALOG;
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = param_1;
            LAB_00496db0:
                /*
                   "Options"
                 */
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(dialogID);
                break;
            case 10:
                /*
                  "Resume Game"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case 0x18:
                dialogID = OpenSHC::UI::Enums::MMT_PAUSE_MENU_OPTIONS;
                goto LAB_00496db0;
            case 0x1a:
                /*
                  "Help"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::openInGameHelpDialog, DAT_TextEditorState::ptr)(
                    0);
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case 0x27:
                /*
                  "Briefing"
                 */
                if (((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CRUSADER_TUTORIAL))
                    && (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION
                             || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1))
                        || ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                            && (DAT_MapPropertiesState::instance.scenarionMissionType != 0)))))) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                    DAT_GameCore::instance.field22_0x64 = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
                break;
            case 0x2c:
                /*
                  "Restart Mission"
                 */
                if ((((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION)
                         && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1))
                        && ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk
                            || (DAT_GameCore::instance.field24_0x6c != 0))))
                    && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                    break;
                goto LAB_00496da8;
            }
            MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        }

    }
}
}
