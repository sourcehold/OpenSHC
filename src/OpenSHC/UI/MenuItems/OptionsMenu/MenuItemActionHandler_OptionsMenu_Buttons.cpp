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

        using Audio::SFX::SpeechEffectID;
        using Game::GameMode;
        using Game::GameMode2;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

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
                if (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAIN_MENU) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                        bVar1 = DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .playerDeathRelated
                            == 0;
                    } else {
                        bVar1 = DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER;
                    }
                    if (!bVar1 || DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT
                        || DAT_GameCore::instance.field24_0x6c
                        || DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL)
                        break;
                }
                /*
                  load
                 */
                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(9);
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case 3:
                /*
                  "Save"
                 */
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        != 0)
                        break;
                } else if (!DAT_GameSynchronyState::instance.isHost)
                    break;
                if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT && !DAT_GameCore::instance.field24_0x6c
                    && DAT_GameCore::instance.gameMode_2 != Game::GM_CRUSADER_TUTORIAL) {
                    /*
                      save
                     */
                    MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::loadOrSaveGame, DAT_MenuTextInputState::ptr)(10);
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
                break;
            case 7:
                /*
                  "Quit mission"
                 */
                if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                    MACRO_CALL_MEMBER(
                        UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_ONLINE_QUIT_GAME, FALSE);
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
            case 9:
                /*
                  "Exit Crusader"
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    Audio::SFX::SEID_GENERAL_QUITGAME);
            LAB_00496da8:
                dialogID = UI::Enums::MMT_YES_NO_DIALOG;
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = param_1;
            LAB_00496db0:
                /*
                   "Options"
                 */
                MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(dialogID);
                break;
            case 10:
                /*
                  "Resume Game"
                 */
                MACRO_CALL_MEMBER(
                    UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case 0x18:
                dialogID = UI::Enums::MMT_PAUSE_MENU_OPTIONS;
                goto LAB_00496db0;
            case 0x1a:
                /*
                  "Help"
                 */
                MACRO_CALL_MEMBER(
                    UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(Text::TextEditorState_Func::openInGameHelpDialog, DAT_TextEditorState::ptr)(0);
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case 0x27:
                /*
                  "Briefing"
                 */
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                    && DAT_GameCore::instance.gameMode_2 != Game::GM_CRUSADER_TUTORIAL
                    && ((DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION
                            || (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1))
                        || ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
                            && (DAT_MapPropertiesState::instance.scenarionMissionType))))) {
                    MACRO_CALL_MEMBER(
                        UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                    DAT_GameCore::instance.gameSuspended = 1;
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
                break;
            case 0x2c:
                /*
                  "Restart Mission"
                 */
                if (DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION
                    && DAT_GameCore::instance.gameMode_2 != Game::GM_ECONOMIC_CAMPAIGN_SH1
                    && (DAT_GameCore::instance.gameMode_2 != Game::GM_BUILDERUnk
                        || (DAT_GameCore::instance.field24_0x6c))
                    && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER)
                    break;
                goto LAB_00496da8;
            }
            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        }

    }
}
}
