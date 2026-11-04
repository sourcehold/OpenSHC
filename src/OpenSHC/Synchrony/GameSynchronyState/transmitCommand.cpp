#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00487C50
    void GameSynchronyState::transmitCommand(byte commandCategory, undefined4 time,
        char* addressOfFullCommandObjectOrCommandParameters, int size, undefined4 idTo)
    {
        if (this->currentGameMode == Game::GM_SOLITARY || this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER
            || this->DPLAYX_4A == NULL) {
            return;
        }
        ++this->transmissionCounterUnk;
        // Small commands go as they are; larger ones are compressed behind the prefix 125.
        if (size <= 200 || commandCategory == Commands::GCT_SEND_RESYNC_LOGICALTILEMAP) {
            this->DAT_Packet.packet.commandProtocol = commandCategory;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::moveLowerThreeBytesIntoParam2, DAT_LowLevelMemory::ptr)(
                &time, &this->DAT_Packet.packet.time);
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                size, addressOfFullCommandObjectOrCommandParameters, this->DAT_Packet.packet.payload);
        } else {
            this->DAT_Packet.prefixedPacket.prefix = 125;
            this->DAT_Packet.prefixedPacket.packet.commandProtocol = commandCategory;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::moveLowerThreeBytesIntoParam2, DAT_LowLevelMemory::ptr)(
                &time, &this->DAT_Packet.prefixedPacket.packet.time);
            int const uncompressedSize = size;
            size = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::compressOrCreateLengthPrefixedPacketUnk, this)(
                       size, addressOfFullCommandObjectOrCommandParameters,
                       this->DAT_Packet.prefixedPacket.packet.payload)
                + 1;
            if (size > uncompressedSize) {
                // A packet that grew is formatted into a debug message that nothing reads.
                char message[1000];
                // "packet size:%d new size:%d type:%d"
                MACRO_CALL(OS_Func::_sprintf)(
                    message, s_packet_size_d_new_size_d_type__005a72b4, uncompressedSize, size, (char)commandCategory);
            }
        }
        this->DAT_CurrentTransmitCommandPacketSize = size;
        if (commandCategory == Commands::GCT_UPDATE_LOBBY_FACE_BITMAPSPECIALTRANSMITLOGIC) {
            if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, idTo,
                    DPSEND_GUARANTEED | DPSEND_ASYNC | DPSEND_NOSENDCOMPLETEMSG, &this->DAT_Packet,
                    size + offsetof(Networking::Packet, payload), 65533, 0, NULL, NULL);
            } else {
                this->DPLAYX_SendAndReceiveREsult
                    = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, idTo, DPSEND_ASYNC | DPSEND_NOSENDCOMPLETEMSG,
                        &this->DAT_Packet, size + offsetof(Networking::Packet, payload), 65533, 0, NULL, NULL);
            }
        } else if (commandCategory == Commands::GCT_ANNOUNCE_PLAYER_INFORMATION_AVAILABLE_AIVSSPECIALTRANSMITLOGIC) {
            this->DPLAYX_SendAndReceiveREsult
                = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, idTo, DPSEND_ASYNC | DPSEND_NOSENDCOMPLETEMSG,
                    &this->DAT_Packet, size + offsetof(Networking::Packet, payload), 65534, 0, NULL, NULL);
        } else {
            this->DPLAYX_SendAndReceiveREsult = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, idTo,
                DPSEND_GUARANTEED | DPSEND_ASYNC | DPSEND_NOSENDCOMPLETEMSG, &this->DAT_Packet,
                size + offsetof(Networking::Packet, payload), 65535, 0, NULL, NULL);
        }
        if (this->DPLAYX_SendAndReceiveREsult != DP_OK && this->DPLAYX_SendAndReceiveREsult != DPERR_PENDING) {
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
        }
    }

}
}
