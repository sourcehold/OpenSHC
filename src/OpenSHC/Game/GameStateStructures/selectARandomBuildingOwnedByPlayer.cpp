#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045AEB0
    int GameStateStructures::selectARandomBuildingOwnedByPlayer(int playerID)
    {
        int buildingCount = this->first500BuildingsCurrentIndexCounter[playerID];
        if (buildingCount <= 0) {
            return 0;
        }
        int buildingIndex = SEC_RNG::instance.currentNumber2 % buildingCount;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        return this->first500BuildingsPerPlayer[playerID][buildingIndex];
    }

}
}
