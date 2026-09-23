#include "../AICState.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDCA0
    int AICState::selectRandomBuildingIDFromListOfBuildingTypes(int playerID, undefined4 param_2)
    {
        int count = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;
        if (count <= 0) {
            return 0;
        }

        int index = SEC_RNG::instance.currentNumber2 % count;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        return DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings[index];
    }

}
}
