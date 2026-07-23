#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0110
    void AICState::setAttackCoordinationLevel(int playerID)
    {
        int const _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType != AITA_NULL) {
            int _willingnessPercentage = (int)this->aics[_aiType - 1].AttCoordinationPreference
                + DAT_GameState::instance.playerDataArray[playerID].currentAttackWave * 4;
            if (90 < _willingnessPercentage) {
                _willingnessPercentage = 90;
            }
            int _rng = (int)SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            if (_rng % 100 < _willingnessPercentage / 2) {
                DAT_GameState::instance.playerDataArray[playerID].aiAttackCoordinationLevel = 2;
                return;
            }
            DAT_GameState::instance.playerDataArray[playerID].aiAttackCoordinationLevel
                = (uint)(_rng % 100 < _willingnessPercentage);
        }
    }
}
}
