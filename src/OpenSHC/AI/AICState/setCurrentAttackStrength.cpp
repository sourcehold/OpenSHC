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
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return;
        int aicIndex = aiType - 1;
        int randomPercent = SEC_RNG::instance.currentNumber2 % 100;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

        DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength
            = (this->aics[aicIndex].AttForceRandom * randomPercent) / 100;
        DAT_GameState::instance.playerDataArray[playerID].currentAttackWave++;

        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] > 10000) {
            DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength
                += DAT_GameState::instance.playerDataArray[playerID].currentAttackWave * 7;
        } else {
            DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength
                += DAT_GameState::instance.playerDataArray[playerID].currentAttackWave * 5;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength > 200) {
            DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength = 200;
        }
    }
}
}
