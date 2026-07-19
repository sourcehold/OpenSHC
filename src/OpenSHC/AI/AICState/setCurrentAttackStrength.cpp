#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDE60
    void AICState::setCurrentAttackStrength(int playerID)
    {
        int const _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType != AITA_NULL) {
            int _randomNumber = (int)SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            int _attForceRandom = (int)this->aics[_aiType - 1].AttForceRandom;
            int* _attackWave = &DAT_GameState::instance.playerDataArray[playerID].currentAttackWave;
            *_attackWave = *_attackWave + 1;
            int _currentGold = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];
            DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength
                = (_attForceRandom * (_randomNumber % 100)) / 100;
            int _currentAttackWave = DAT_GameState::instance.playerDataArray[playerID].currentAttackWave;
            if (_currentGold < 10001) {
                int* _ptrAttackStrength
                    = &DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength;
                *_ptrAttackStrength = *_ptrAttackStrength + _currentAttackWave * 5;
            } else {
                int* _ptrAttackStrength
                    = &DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength;
                *_ptrAttackStrength = *_ptrAttackStrength + _currentAttackWave * 7;
            }
            if (200 < DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength) {
                DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength = 200;
            }
        }
    }
}
}
