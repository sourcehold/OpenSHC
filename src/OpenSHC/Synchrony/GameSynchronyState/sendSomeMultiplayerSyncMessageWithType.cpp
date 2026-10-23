#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00487E30
    void GameSynchronyState::sendSomeMultiplayerSyncMessageWithType(undefined4 syncPacketType2)
    {
        if (this->currentGameMode != Game::GM_SOLITARY && this->currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
            && this->DPLAYX_4A != (IDirectPlay4A*)0x0) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::moveLowerThreeBytesIntoParam2, DAT_LowLevelMemory::ptr)(
                &DAT_GameCore::instance.mapTimeInTicks, &this->mapTimeInTicksLower3Bytes);
            this->syncPacket2Type = (undefined1)syncPacketType2;
            this->syncParamTimeDiff = (undefined1)this->clTimeDiff;
            // The payload is the three adjacent fields written just above, so dwDataSize is
            // their combined size. The 65533 is dwPriority, and stays a plain number: dplay.h
            // names only the top of that range (DPSEND_MAX_PRIORITY, 0xFFFF) and nothing shows
            // this value is derived from it.
            size_t const _packetSize = sizeof(this->syncPacket2Type) + sizeof(this->mapTimeInTicksLower3Bytes)
                + sizeof(this->syncParamTimeDiff);
            this->DPLAYX_SendAndReceiveREsult
                = this->DPLAYX_4A->SendEx(this->DPLAYX_PlayerHandle, 0, DPSEND_NOSENDCOMPLETEMSG | DPSEND_ASYNC,
                    &this->syncPacket2Type, _packetSize, 65533, 0, (void*)0x0, (DWORD_PTR*)0x0);
            if ((this->DPLAYX_SendAndReceiveREsult) && (this->DPLAYX_SendAndReceiveREsult != -0x7ffffff6)) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::handleUnexpectedDPlayXResult, this)();
            }
            uint _playerID = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
                this)(this->DPLAYX_PlayerHandle);
            this->matchTimes[_playerID] = DAT_GameCore::instance.mapTimeInTicks;
            ++this->receivedMatchTimesTrackerUnk;
            if (6 < this->receivedMatchTimesTrackerUnk) {
                --this->commandDelay;
                this->receivedMatchTimesTrackerUnk = 0;
                if (!this->syncRelatedCountdown) {
                    int _maxLatency = 0;
                    for (int _player = 1; _player < 9; ++_player) {
                        if ((this->currentPlayerFullIDArray[_player] != -1)
                            && (this->connectionLagInfoArray[_player].average1 > _maxLatency)) {
                            _maxLatency = this->connectionLagInfoArray[_player].average1;
                        }
                    }
                    int _countdown;
                    if (_maxLatency < 2) {
                        _countdown = 20;
                    } else if (_maxLatency == 2) {
                        _countdown = 25;
                    } else {
                        _countdown = _maxLatency + 27;
                        if (50 < _countdown) {
                            _countdown = 50;
                        }
                    }
                    if (this->commandDelay < _countdown) {
                        this->commandDelay = _countdown;
                    }
                }
                --this->clTimeDiff;
                if (this->clTimeDiff < 0) {
                    this->clTimeDiff = 0;
                }
            }
        }
    }

}
}
