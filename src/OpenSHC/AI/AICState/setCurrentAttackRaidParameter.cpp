#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDF10
    void AICState::setCurrentAttackRaidParameter(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return;
        int aicIndex = aiType - 1;

        int randomPercent = SEC_RNG::instance.currentNumber2 % 100;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

        int attackedPlayerID = DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk;
        int raidUnits = this->aics[aicIndex].RaidUnitsRandom;
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] < 1000) {
            raidUnits = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
            >= 5000) {
            raidUnits *= 2;
        }

        if (DAT_GameState::instance.playerDataArray[attackedPlayerID].currentResources[Game::Resources::RT_GOLD]
            < 500) {
            raidUnits = -(this->aics[aicIndex].RaidUnitsBase / 2);
        }

        DAT_GameState::instance.playerDataArray[playerID].currentAttackRaidParameter
            = (raidUnits * randomPercent) / 100;
    }
}
}
