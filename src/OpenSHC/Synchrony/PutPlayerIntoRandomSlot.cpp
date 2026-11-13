#include "../Synchrony.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00428480
void Synchrony::PutPlayerIntoRandomSlot(int param_1)
{
    for (int slot = 0; slot < 8; ++slot) {
        if (DAT_GameSynchronyState::instance.playerPositionsArray[slot] == param_1 - 1) {
            return;
        }
    }
    int usableSlots = 0;
    int takenSlots = 0;
    for (int slot = 0; slot < 8; ++slot) {
        if (DAT_GameCore::instance.keepPositions[slot].x < 0) {
            continue;
        }
        ++usableSlots;
        if (DAT_GameSynchronyState::instance.playerPositionsArray[slot] >= 0) {
            ++takenSlots;
        }
    }
    if (usableSlots <= takenSlots) {
        return;
    }
    int freeIndex = SEC_RNG::instance.currentNumber1 % (usableSlots - takenSlots);
    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
    for (int slot = 0; slot < 8; ++slot) {
        if (DAT_GameCore::instance.keepPositions[slot].x >= 0
            && DAT_GameSynchronyState::instance.playerPositionsArray[slot] < 0) {
            if (--freeIndex < 0) {
                DAT_GameSynchronyState::instance.playerPositionsArray[slot] = param_1 - 1;
                return;
            }
        }
    }
}

}
