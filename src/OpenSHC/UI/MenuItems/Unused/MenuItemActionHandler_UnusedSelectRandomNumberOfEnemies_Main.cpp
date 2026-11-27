// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042BA50
        void Unused::MenuItemActionHandler_UnusedSelectRandomNumberOfEnemies_Main(int enemyCount, ...)
        {
            // a single-player skirmish lobby with the player in slot 1 and enemyCount random AI lords after it
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
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[1],
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_ZERO));
            DAT_GameSynchronyState::instance.currentPlayerSlotID = 0;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
            for (int slot = 0; slot < countof(DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue); ++slot) {
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[slot] = 1;
            }
            // enemy + 1 written out each time (a slot local: quick_diff 0.9861 -> 0.6207)
            for (int enemy = 1; enemy <= enemyCount; ++enemy) {
                DAT_GameSynchronyState::instance.currentAIArray[enemy + 1]
                    = SEC_RNG::instance.currentNumber1 % DAT_GameCore::instance.numOfAIsWithCastleUnk + 1;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                MACRO_CALL(OpenSHC::Synchrony_Func::ResetAiVariationArrayValue)(enemy + 1);
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[enemy + 1] = 1;
            }
        }

    }
}
}
