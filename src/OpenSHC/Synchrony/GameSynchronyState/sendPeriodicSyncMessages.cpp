#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C750
    void GameSynchronyState::sendPeriodicSyncMessages()
    {
        DWORD _now = timeGetTime();
        if (1800 < (int)(_now - this->otherTime1)) {
            this->otherTime1 = _now;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendSyncPacket126, this)();
        }
        if (180 <= (int)(_now - this->now2)) {
            this->now2 = _now;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendSomeMultiplayerSyncMessageWithType, this)(0);
            if (0 < this->syncRelatedCountdown) {
                --this->syncRelatedCountdown;
            }
        }
    }

}
}
