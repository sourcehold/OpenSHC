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
        if (aiType == AITA_NULL) {
            return;
        }

        int randomPercent = SEC_RNG::instance.currentNumber2 % 100;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

        int raidUnits = this->aics[aiType - 1].RaidUnitsRandom;
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] < 1000) {
            raidUnits = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] >= 5000) {
            raidUnits *= 2;
        }

        if (DAT_GameState::instance
                .playerDataArray[DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk]
                .currentResources[0xf]
            < 500) {
            raidUnits = -(this->aics[aiType - 1].RaidUnitsBase / 2);
        }

        DAT_GameState::instance.playerDataArray[playerID].currentAttackRaidParameter
            = (raidUnits * randomPercent) / 100;
    }
}
}
