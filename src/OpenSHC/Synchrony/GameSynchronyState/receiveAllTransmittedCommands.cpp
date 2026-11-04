// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00490690
    void GameSynchronyState::receiveAllTransmittedCommands()
    {
        this->lastCommandReceiveTime = timeGetTime();
        // Reads every packet DirectPlay has queued, until there is none left.
        for (; this->currentGameMode != Game::GM_SOLITARY;) {
            if (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER || this->DPLAYX_4A == NULL) {
                return;
            }
            this->DPLAY_ReceiveDataSize = sizeof(this->DPLAY_ReceiveData);
            this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->Receive(&this->DPLAYX_ReceivedPlayerID,
                &this->DPLAY_ToID, DPRECEIVE_ALL, &this->DPLAY_ReceiveData, &this->DPLAY_ReceiveDataSize);
            if (this->DPLAYX_SendAndReceiveREsult == DPERR_PENDING
                || this->DPLAYX_SendAndReceiveREsult == DPERR_NOMESSAGES) {
                return;
            }
            if (this->DPLAYX_SendAndReceiveREsult != DP_OK) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
                return;
            }
            if (this->DPLAYX_ReceivedPlayerID == DPID_SYSMSG) {
                DPMSG_GENERIC const* const systemMessage = (DPMSG_GENERIC const*)&this->DPLAY_ReceiveData;
                DWORD const messageType = systemMessage->dwType;
                if (messageType == DPSYS_CREATEPLAYERORGROUP) {
                    continue;
                }
                if (messageType == DPSYS_DESTROYPLAYERORGROUP) {
                    // The leave reason removePlayerFromLobby sends on: 61, the player left (62 is a lag kick, 63 a
                    // missed resync).
                    this->kickDueToLagStatusUnk = 61;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::removePlayerFromLobby, this)(
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
                            this)(((DPMSG_DESTROYPLAYERORGROUP const*)systemMessage)->dpId));
                    continue;
                }
                if (messageType == DPSYS_SESSIONLOST) {
                    continue;
                }
                if (messageType == DPSYS_HOST) {
                    // The host left and this player takes over. Setting isHost and the message through the global
                    // instance is needed for the match.
                    DAT_GameSynchronyState::instance.isHost = TRUE;
                    this->DAT_HashCountdown = 2;
                    this->timeSkirmishGameStart = timeGetTime();
                    for (int player = 0; player < 9; ++player) {
                        this->HASH_HashTotal[player] = 0;
                        this->DAT_PlayerMatchTimes[player] = 0;
                    }
                    // "You are now Host"
                    strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 60));
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 0);
                    if (!MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                        if (DAT_MenuModalComposition1::instance.activeModalDialogID == UI::Enums::MMT_ROUNDTABLE) {
                            DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                        }
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                            DAT_GameSynchronyState::ptr)();
                    }
                } else {
                    // Any other system message is formatted into a debug text that nothing reads.
                    char text[100];
                    // "DP SYS Message: %x"
                    MACRO_CALL(OS_Func::_sprintf)(text, s_DP_SYS_Message___x_005a74c0, messageType);
                }
                continue;
            }
            if (this->DPLAYX_ReceivedPlayerID == this->DPLAYX_PlayerHandle) {
                continue;
            }
            if (this->DPLAY_ReceiveData.packet.commandProtocol == 125) {
                // A compressed packet: move its header down over the prefix and unpack the rest behind it.
                for (int i = 0; i < 4; ++i) {
                    ((byte*)&this->DPLAY_ReceiveData.packet)[i] = ((byte*)&this->DPLAY_ReceiveData.packet)[i + 1];
                }
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::decompressTooLongPacketData, this)(
                    this->DPLAY_ReceiveData.prefixedPacket.packet.payload, this->DPLAY_ReceiveData.packet.payload);
            }
            this->receivedCommandMapTimeInTicks = 0;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::moveLowerThreeBytesIntoParam2, DAT_LowLevelMemory::ptr)(
                &this->DPLAY_ReceiveData.packet.time, &this->receivedCommandMapTimeInTicks);
            if (this->DPLAY_ReceiveData.packet.commandProtocol >= 126) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::computeAndSetLatencyInformation, this)();
            } else if (this->DPLAY_ReceiveData.packet.commandProtocol >= 2) {
                ++this->packetsReceived;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::scheduleReceivedCommand, this)(
                    this->DPLAY_ReceiveData.packet.commandProtocol, this->DPLAYX_ReceivedPlayerID,
                    this->receivedCommandMapTimeInTicks, this->DPLAY_ReceiveData.packet.payload);
            } else {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::processSyncPacket, this)(
                    this->DPLAY_ReceiveData.packet.commandProtocol);
            }
        }
    }

}
}
