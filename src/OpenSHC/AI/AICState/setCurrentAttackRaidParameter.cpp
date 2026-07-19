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
        int const _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType != AITA_NULL) {
            int _rng = (int)SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            AICSpecification const* spec = &this->aics[_aiType - 1];
            int _gold = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];
            int _raidUnitsRandom = (int)spec->RaidUnitsRandom;
            if (_gold < 1000) {
                _raidUnitsRandom = 0;
            } else if (4999 < _gold) {
                _raidUnitsRandom = _raidUnitsRandom * 2;
            }
            if (DAT_GameState::instance
                    .playerDataArray[DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk]
                    .currentResources[0xf]
                < 500) {
                _raidUnitsRandom = -((int)spec->RaidUnitsBase / 2);
            }
            DAT_GameState::instance.playerDataArray[playerID].currentAttackRaidParameter
                = (_raidUnitsRandom * (_rng % 100)) / 100;
        }
    }
}
}
