#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

#include "stdlib.h"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00488010
    void GameSynchronyState::processSyncPacket(int param_1)
    {
        uint _player = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::translateMultiplayerIDsIntoPlayerIDs,
            this)(this->DPLAYX_ReceivedPlayerID);
        this->matchTimes[_player]
            = this->receivedCommandMapTimeInTicks + this->connectionLagInfoArray[_player].average1;
        int _countDown = this->commandDelay;
        int _delay = (char)this->DPLAY_ReceiveData.packet.payload[0] + 10;
        if (_delay > _countDown) {
            int _cappedDelay = _countDown + 5;
            if (_delay >= _cappedDelay) {
                _delay = _cappedDelay;
            }
            this->commandDelay = _delay;
        }
        uint _difference = (DAT_GameCore::instance.mapTimeInTicks - this->receivedCommandMapTimeInTicks)
            - this->connectionLagInfoArray[_player].average1;
        int _absoluteDifference = abs((int)_difference);
        if (this->clTimeDiff < _absoluteDifference) {
            int _newDiff = this->clTimeDiff + 5;
            if (_absoluteDifference >= _newDiff) {
                _absoluteDifference = _newDiff;
            }
            this->clTimeDiff = _absoluteDifference;
            if (45 < _absoluteDifference) {
                this->clTimeDiff = 45;
            }
        }
        int _newDiff2 = this->clTimeDiff + 10;
        if (_newDiff2 > this->commandDelay) {
            int _capped = _countDown + 5;
            if (_newDiff2 >= _capped) {
                _newDiff2 = _capped;
            }
            this->commandDelay = _newDiff2;
        }
        if (this->syncRelatedCountdown) {
            this->commandDelay = 1;
        }
    }

}
}
