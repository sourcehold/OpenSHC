// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

#include <stdlib.h>
#include <string.h>

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00491040
    void GameSynchronyState::handleCommandLineArguments(char* arguments)
    {
        bool quoted = false;
        bool done = false;
        this->useTCPIP = FALSE;
        if (strlen(arguments) == 0) {
            return;
        }
        // The arguments come as pairs of words, an option and its value; either may be quoted.
        char words[4][256];
        words[0][0] = '\0';
        words[1][0] = '\0';
        int word = 0;
        int length = 0;
        for (int index = 0; !done;) {
            char const character = arguments[index];
            if (character == '"') {
                ++index;
                quoted = !quoted;
                if (quoted) {
                    continue;
                }
                words[word][length] = '\0';
                length = 0;
                char const next = arguments[index + 1];
                if (next != '+' && (next != '"' || arguments[index + 2] != '+') && word != 1) {
                    ++word;
                    continue;
                }
                word = 0;
            } else if (character == '\0') {
                words[word][length] = '\0';
                length = 0;
                done = true;
            } else if (character == ' ') {
                if (quoted) {
                    words[word][length] = ' ';
                    ++length;
                    ++index;
                    continue;
                }
                char const next = arguments[index + 1];
                ++index;
                words[word][length] = '\0';
                length = 0;
                if (next != '+' && (next != '"' || arguments[index + 1] != '+') && word != 1) {
                    ++word;
                    continue;
                }
                word = 0;
            } else {
                words[word][length] = character;
                ++length;
                ++index;
                continue;
            }
            strcpy(words[2], words[0]);
            strcpy(words[3], words[1]);
            // The options are "+connect", "+host" and "+name".
            if (MACRO_CALL(OS_Func::__stricmp)(s__connect_005a74e4, words[0]) == 0) {
                this->useTCPIP = TRUE;
                // The address goes into connectTarget, leaving its last byte 0; a port follows a colon.
                int const targetLength = min(strlen(words[1]), sizeof(this->connectTarget) - 1);
                memset(this->connectTarget, 0, sizeof(this->connectTarget));
                int colon = 0;
                for (; colon < targetLength; ++colon) {
                    char const targetCharacter = words[1][colon];
                    this->connectTarget[colon] = targetCharacter;
                    if (targetCharacter == ':') {
                        this->connectPort = atol(words[1] + colon + 1);
                        break;
                    }
                }
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(5);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                    words[3]);
                if (this->connectPort != 0) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                        words[3] + colon + 1);
                }
            } else if (MACRO_CALL(OS_Func::__stricmp)(s__host_005a74dc, words[0]) == 0) {
                this->useTCPIP = TRUE;
                this->willHost = 1;
                this->connectPort = atol(words[1]);
                if (this->connectPort != 0) {
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(6);
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                        words[3]);
                }
            } else if (MACRO_CALL(OS_Func::__stricmp)(s__name_005a74d4, words[0]) == 0) {
                strcpy((char*)this->connectName, words[1]);
            }
            words[0][0] = '\0';
            words[1][0] = '\0';
        }
        if (!this->useTCPIP) {
            return;
        }
        if (strlen(MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0))
            == 0) {
            // Without a player name the default one is used: "Lord Crusader" from the game options texts.
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(0);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_GAME_OPTIONS, 48));
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
        }
        // The original sets isHost and starts the session through the global instance.
        DAT_GameSynchronyState::instance.isHost = this->willHost;
        if (this->willHost) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::initializeMultiplayerLobby, this)();
            if (MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                    DAT_GameSynchronyState::ptr)(FALSE)
                < 0) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::disconnectDPlay, this)();
            } else {
                DAT_GameSynchronyState::instance.field_0x106ee4 = 1;
                DAT_GameCore::instance.menuTabToSwitchTo.tabType = 0;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_LOBBY_MENU, 0);
                MACRO_CALL(Synchrony_Func::InitSkirmishLobbyData)();
                Menu_LobbyMenu::instance.thousand = 0;
                MACRO_CALL_MEMBER(
                    Synchrony::GameSynchronyState_Func::waitForMultiplayerHost, DAT_GameSynchronyState::ptr)();
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
            }
        } else {
            this->nextModalDialog = UI::Enums::MMT_WAITING_FOR_HOST;
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_MP_CONNECTION, 0);
            this->multiplayerJoinStep = 0;
        }
    }

}
}
