#include "../OnlineVoteQuitAndQuitGame.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::UI::Enums::MenuModalType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00495860
        void OnlineVoteQuitAndQuitGame::MenuItemActionHandler_OnlineVoteQuitAndQuitGame_Main(int param_1, ...)
        {
            byte bVar1;
            switch (param_1) {
            case 2:
                bVar1 = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
                    bVar1 = bVar1 + 1;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
                    bVar1 = bVar1 + 1;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
                    bVar1 = bVar1 + 1;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
                    bVar1 = bVar1 + 1;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
                    bVar1 = bVar1 + 1;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
                    bVar1 = bVar1 + 1;
                }
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
                    bVar1 = bVar1 + 1;
                }
                if (1 < bVar1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (OpenSHC::Commands::GameCommandType)(OpenSHC::Commands::GCT_BROADCAST_SYNC_RELATED_STATUS_1
                            | OpenSHC::Commands::GCT_MULTIPLAYER_ANNOUNCE_HOST));
                    DAT_GameSynchronyState::instance.quitGameVoteRelated = 2;
                    DAT_GameSynchronyState::instance.field122_0xc70[1]
                        = (int)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] == -1);
                    DAT_GameSynchronyState::instance.field122_0xc70[2]
                        = (int)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] == -1);
                    DAT_GameSynchronyState::instance.field122_0xc70[3]
                        = (int)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] == -1);
                    DAT_GameSynchronyState::instance.field122_0xc70[4]
                        = (int)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] == -1);
                    DAT_GameSynchronyState::instance.field122_0xc70[5]
                        = (int)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] == -1);
                    DAT_GameSynchronyState::instance.field122_0xc70[6]
                        = (int)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] == -1);
                    DAT_GameSynchronyState::instance.field122_0xc70[7]
                        = (int)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] == -1);
                    DAT_GameSynchronyState::instance.field122_0xc70[8]
                        = (int)(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] == -1);
                    DAT_GameSynchronyState::instance
                        .field122_0xc70[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                    DAT_GameSynchronyState::instance.quitGameVoteRequestTime = timeGetTime();
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
            case 1:
                DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_MULTIPLAYER_END_OF_GAME;
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                MACRO_CALL(
                    OpenSHC::UI::MenuItems::General_Func::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(
                    0x16);
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            case 3:
                goto switchD_00495871_caseD_3;
            case 4:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                break;
            case 5:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                break;
            default:
            switchD_00495871_caseD_5:
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
            }
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_SEND_QUIT_GAME_VOTE);
        switchD_00495871_caseD_3:
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            goto switchD_00495871_caseD_5;
        }

    }
}
}
