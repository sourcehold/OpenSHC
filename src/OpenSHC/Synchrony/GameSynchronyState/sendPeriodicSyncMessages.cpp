#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C750
    void GameSynchronyState::sendPeriodicSyncMessages()
    {
        unsigned int const now = timeGetTime();
        // The native comparisons use signed, wrapping 32-bit elapsed values.
        if (static_cast<int>(now - static_cast<unsigned int>(otherTime1)) > 1800) {
            otherTime1 = now;
            MACRO_CALL_MEMBER(GameSynchronyState_Func::sendSyncPacket126, this)();
        }
        if (static_cast<int>(now - static_cast<unsigned int>(now2)) >= 180) {
            now2 = now;
            MACRO_CALL_MEMBER(GameSynchronyState_Func::sendSomeMultiplayerSyncMessageWithType, this)(0);
            if (syncRelatedCountdown > 0)
                --syncRelatedCountdown;
        }
    }

}
}
