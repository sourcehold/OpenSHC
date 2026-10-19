#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

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
        int iVar2 = (char)this->DPLAY_ReceiveData.packet.payload[0] + 10;
        if (iVar2 > _countDown) {
            int iVar1 = _countDown + 5;
            if (iVar2 >= iVar1) {
                iVar2 = iVar1;
            }
            this->commandDelay = iVar2;
        }
        uint _difference = (DAT_GameCore::instance.mapTimeInTicks - this->receivedCommandMapTimeInTicks)
            - this->connectionLagInfoArray[_player].average1;
        int _absoluteDifference = abs((int)_difference);
        if ((int)this->clTimeDiff < _absoluteDifference) {
            int _newDiff = this->clTimeDiff + 5;
            if (_absoluteDifference >= _newDiff) {
                _absoluteDifference = _newDiff;
            }
            this->clTimeDiff = _absoluteDifference;
            if (0x2d < _absoluteDifference) {
                this->clTimeDiff = 45;
            }
        }
        int _newDiff2 = this->clTimeDiff + 10;
        if (_newDiff2 > (int)this->commandDelay) {
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
