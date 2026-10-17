#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004591B0
    int GameStateStructures::getNumberToDisplayBribeIncome(int playerIndex, int taxStep, int currentPopulation)
    {
        int bribeIncome = 0;
        if (taxStep < 3) {
            bribeIncome = MACRO_CALL_MEMBER(
                              OpenSHC::Game::GameStateStructures_Func::calculateTaxBribeExpenseForPlayer, this)(
                              playerIndex, taxStep, currentPopulation)
                * 4;
        }
        return bribeIncome / 10;
    }

}
}
