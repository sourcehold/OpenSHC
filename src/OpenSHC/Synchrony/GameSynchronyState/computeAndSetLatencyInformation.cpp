#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004882A0
    void GameSynchronyState::computeAndSetLatencyInformation()
    {
        if (this->DPLAY_ReceiveData.packet.commandProtocol == 126) {
            // A ping: answer it with 127 and the ping's counter.
            this->syncPacketType = 127;
            this->syncRelatedCounter = this->DPLAY_ReceiveData.prefixedPacket.packet.commandProtocol;
            this->DPLAYX_SendAndReceiveREsult
                = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, this->DPLAYX_ReceivedPlayerID,
                    DPSEND_GUARANTEED | DPSEND_ASYNC | DPSEND_NOSENDCOMPLETEMSG, &this->syncPacketType,
                    sizeof(this->syncPacketType) + sizeof(this->syncRelatedCounter), 65000, 0, NULL, NULL);
            if (this->DPLAYX_SendAndReceiveREsult != DP_OK && this->DPLAYX_SendAndReceiveREsult != DPERR_PENDING) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
            }
            return;
        }
        // The answer to this player's ping: half the round trip in map ticks and in milliseconds.
        uint const player = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
            this)(this->DPLAYX_ReceivedPlayerID);
        this->connectionLagInfoArray[player].time = timeGetTime();
        if (this->connectionLagInfoArray[player].counter
            != this->DPLAY_ReceiveData.prefixedPacket.packet.commandProtocol) {
            return;
        }
        this->connectionLagInfoArray[player].subtractedMapTicks
            = (int)(DAT_GameCore::instance.mapTimeInTicks - this->connectionLagInfoArray[player].mapTimeInTicks) / 2;
        this->connectionLagInfoArray[player].subtractedTime
            = (timeGetTime() - this->connectionLagInfoArray[player].now) / 2;
        if (!MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            return;
        }
        this->connectionLagInfoArray[player].checkFor0 = 1;
        int mapTicksSum = 0;
        int timeSum = 0;
        // The first answer fills the whole history; later ones go in turn.
        if (this->counter == -1) {
            for (int entry = 0; entry < this->limit; ++entry) {
                this->historicalLagInfoPerPlayer[player][entry][0]
                    = this->connectionLagInfoArray[player].subtractedMapTicks;
                this->historicalLagInfoPerPlayer[player][entry][1]
                    = this->connectionLagInfoArray[player].subtractedTime;
            }
            this->counter = 0;
        } else {
            this->historicalLagInfoPerPlayer[player][this->counter][1]
                = this->connectionLagInfoArray[player].subtractedTime;
            this->historicalLagInfoPerPlayer[player][this->counter][0]
                = this->connectionLagInfoArray[player].subtractedMapTicks;
            ++this->counter;
            if (this->counter >= this->limit) {
                this->counter = 0;
            }
        }
        int const historyLength = this->limit;
        if (historyLength == 0) {
            return;
        }
        // fixme: the time is read two entries ahead of the map ticks; with limit > 98 this reads past the player's
        // history.
        for (int entry = 0; entry < this->limit; ++entry) {
            mapTicksSum += this->historicalLagInfoPerPlayer[player][entry][0];
            timeSum += this->historicalLagInfoPerPlayer[player][entry + 2][1];
        }
        this->connectionLagInfoArray[player].average2 = timeSum / historyLength;
        this->connectionLagInfoArray[player].average1 = mapTicksSum / historyLength;
    }

}
}
