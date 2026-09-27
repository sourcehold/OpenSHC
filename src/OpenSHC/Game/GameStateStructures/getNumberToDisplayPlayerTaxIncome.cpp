#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459170
    int GameStateStructures::getNumberToDisplayPlayerTaxIncome(int playerIndex, int taxStep, int currentPopulation)
    {
        int taxIncome = 0;
        if (taxStep > 3) {
            taxIncome = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateTaxIncomeForPlayer, this)(
                            playerIndex, taxStep, currentPopulation)
                * 4;
        }
        return taxIncome / 10;
    }

}
}
