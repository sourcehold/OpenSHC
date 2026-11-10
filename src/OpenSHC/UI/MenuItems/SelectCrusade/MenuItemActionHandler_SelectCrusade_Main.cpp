// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../SelectCrusade.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042BF00
        void SelectCrusade::MenuItemActionHandler_SelectCrusade_Main(int buttonID, ...)
        {
            if (buttonID == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                return;
            }
            if (buttonID != 1 && buttonID != 3 && buttonID != 4) {
                if (buttonID != 2) {
                    return;
                }
                // button 2: custom skirmish
                DAT_GameCore::instance.isSkirmishTrail = FALSE;
                DAT_GameSynchronyState::instance.field_0x106ee4 = 1;
                DAT_GameCore::instance.menuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_NONE;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_LOBBY_MENU, 0);
                MACRO_CALL(OpenSHC::Synchrony_Func::InitSkirmishLobbyData)();
                Menu_LobbyMenu::instance.thousand = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Synchrony::GameSynchronyState_Func::setupSkirmishLobby, DAT_GameSynchronyState::ptr)();
                DAT_GameSynchronyState::instance.isHost = TRUE;
                DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER;
                DAT_GameSynchronyState::instance.DPLAYX_ReceivedPlayerID = 1;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER;
                MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_GameSynchronyState::instance.DAT_PlayerNames, 0,
                    sizeof(DAT_GameSynchronyState::instance.DAT_PlayerNames));
                // the player's name
                strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[1],
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0));
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 0;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                for (int slot = 0; slot < countof(DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue);
                    ++slot) {
                    DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[slot] = 1;
                }
                return;
            }
            DAT_GameCore::instance.gameSuspended = 0;
            if (buttonID == 4) {
                DAT_GameCore::instance.currentTrailType = OpenSHC::Game::TT_EXTREME;
            } else if (buttonID == 3) {
                DAT_GameCore::instance.currentTrailType = OpenSHC::Game::TT_WARCHEST;
            } else {
                DAT_GameCore::instance.currentTrailType = OpenSHC::Game::TT_FIRST_EDITION;
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                OpenSHC::UI::Enums::MVT_CRUSADE_MAP, 0);
        }

    }
}
}
