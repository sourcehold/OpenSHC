#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDCA0
    int AICState ::selectRandomBuildingIDFromListOfBuildingTypes(int playerID, undefined4 param_2)

    {

        int iVar1;

        int iVar2;

        iVar1 = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;

        if (iVar1 < 1) {

            return 0;
        }

        iVar2 = (int)SEC_RNG::instance.currentNumber2;

        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

        return (int)DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings[iVar2 % iVar1];
    }

}
}
