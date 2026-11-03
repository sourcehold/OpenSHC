#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using DE::SHCDE::eTextSections;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048BD40
    void GameSynchronyState::compareGameVersions()
    {
        BOOLEnum const wasMatching = this->flag_0x7aad8;
        int firstVersion = -1;
        int lowestVersion = 0x7fffffff;
        this->flag_0x7aad8 = TRUE;
        int player;
        for (player = 1; player < 9; player++) {
            if (this->currentPlayerFullIDArray[player] != -1) {
                if (!this->isIncludedPlayer[player]) {
                    this->flag_0x7aad8 = TRUE;
                    break;
                }
                if (firstVersion == -1) {
                    firstVersion = this->DAT_MultiplayerGameVersions[player];
                } else if (firstVersion != this->DAT_MultiplayerGameVersions[player]) {
                    this->flag_0x7aad8 = FALSE;
                }
                if (lowestVersion > this->DAT_MultiplayerGameVersions[player]) {
                    lowestVersion = this->DAT_MultiplayerGameVersions[player];
                }
            }
        }
        if (!this->flag_0x7aad8) {
            if ((wasMatching)
                && (this->DAT_MultiplayerGameVersions[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    > lowestVersion)) {
                /*
                  added by script: "Someone has an old version, please get him or her to   upgrade"
                 */
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_MP_VERSION_CONTROL, 2));
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 0);
                int savedReceivers[9];
                for (int receiver = 0; receiver < 9; receiver++) {
                    savedReceivers[receiver] = this->DAT_ChatMessageReceiverArray[receiver];
                    this->DAT_ChatMessageReceiverArray[receiver] = 0;
                    // As in the original, this tests the first loop's last player, not the receiver.
                    if (this->currentPlayerFullIDArray[player] != -1
                        && this->DAT_MultiplayerGameVersions[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            > this->DAT_MultiplayerGameVersions[receiver]) {
                        this->DAT_ChatMessageReceiverArray[receiver] = 1;
                    }
                }
                this->DAT_ChatTauntOrMessage = 0;
                char currentText[100];
                strcpy(currentText,
                    MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)());
                /*
                  added by script: "You have an old version, please upgrade to the latest   version"
                 */
                char* const oldVersionText = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MP_VERSION_CONTROL, 1);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                    DAT_UserTextHandlerState::ptr)(4, oldVersionText);
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_TAUNT_OR_CHAT);
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                    DAT_UserTextHandlerState::ptr)(4, currentText);
                for (int receiver = 0; receiver < 9; receiver++) {
                    this->DAT_ChatMessageReceiverArray[receiver] = savedReceivers[receiver];
                }
            }
            if (DAT_GameSynchronyState::instance
                    .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                != 0) {
                DAT_GameSynchronyState::instance
                    .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
            }
        }
    }

}
}
