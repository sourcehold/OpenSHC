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
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0042BA50
        void Unused::MenuItemActionHandler_UnusedSelectRandomNumberOfEnemies_Main(int param_1, ...)
        {
            int playerID;
            char cVar1;
            char* pcVar2;
            char (*pacVar3)[250];
            int iVar4;
            DAT_GameSynchronyState::instance.field225_0x106ee4 = 1;
            DAT_GameCore::instance.menuTabToSwitchTo.tabType = ((BuildingsAndStatusMenuTabType)0);
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
            MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_GameSynchronyState::instance.DAT_PlayerNames, 0, 0x8ca);
            pcVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
            pacVar3 = DAT_GameSynchronyState::instance.DAT_PlayerNames + 1;
            do {
                cVar1 = *pcVar2;
                (*pacVar3)[0] = cVar1;
                pcVar2 = pcVar2 + 1;
                pacVar3 = (char (*)[250])(*pacVar3 + 1);
            } while (cVar1 != '\0');
            DAT_GameSynchronyState::instance.currentPlayerSlotID = 0;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[0] = 1;
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[1] = 1;
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[2] = 1;
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[3] = 1;
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[4] = 1;
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[5] = 1;
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[6] = 1;
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[7] = 1;
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[8] = 1;
            iVar4 = 1;
            if (0 < param_1) {
                do {
                    DAT_GameSynchronyState::instance.currentAIArray[iVar4 + 1]
                        = (int)SEC_RNG::instance.currentNumber1 % DAT_GameCore::instance.numOfAIsWithCastleUnk + 1;
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                    playerID = iVar4 + 1;
                    MACRO_CALL(OpenSHC::Synchrony_Func::ResetAiVariationArrayValue)(playerID);
                    DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[iVar4 + 1] = 1;
                    iVar4 = playerID;
                } while (playerID <= param_1);
            }
        }

    }
}
}
