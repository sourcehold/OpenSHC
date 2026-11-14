#include "../OnlineVoteQuitAndQuitGame.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00495860
        void OnlineVoteQuitAndQuitGame::MenuItemActionHandler_OnlineVoteQuitAndQuitGame_Main(int button, ...)
        {
            // the cases in the original's block order
            switch (button) {
            case 1:
                DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_MULTIPLAYER_END_OF_GAME;
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                MACRO_CALL(
                    OpenSHC::UI::MenuItems::General_Func::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(
                    22);
                break;
            case 2: {
                // a vote needs someone else to answer it
                int playerCount = 0;
                for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++slot) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] != -1) {
                        playerCount++;
                    }
                }
                if (playerCount > 1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_91);
                    DAT_GameSynchronyState::instance.quitGameVoteRelated = 2;
                    // the empty slots count as yes votes, and so does the player asking
                    for (int slot = 1; slot < countof(DAT_GameSynchronyState::instance.quitGameVoteArray); ++slot) {
                        DAT_GameSynchronyState::instance.quitGameVoteArray[slot]
                            = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] == -1;
                    }
                    DAT_GameSynchronyState::instance
                        .quitGameVoteArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                    DAT_GameSynchronyState::instance.quitGameVoteRequestTime = timeGetTime();
                    break;
                }
                // alone in the game, the player quits at once, as with button 1: the code is repeated here rather
                // than falling into case 1, for the match
                DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_MULTIPLAYER_END_OF_GAME;
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                MACRO_CALL(
                    OpenSHC::UI::MenuItems::General_Func::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(
                    22);
                break;
            }
            case 4:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_QUIT_GAME_VOTE);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                break;
            case 5:
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_QUIT_GAME_VOTE);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                break;
            case 3:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        }

    }
}
}
