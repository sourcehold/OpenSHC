#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004591B0
    int GameStateStructures::getNumberToDisplayBribeIncome(int playerIndex, int taxStep, int currentPopulation)
    {
        int iVar1 = 0;
        if (taxStep < 3) {
            iVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateTaxBribeExpenseForPlayer, this)(
                playerIndex, taxStep, currentPopulation);
            iVar1 = iVar1 * 4;
        }
        return iVar1 / 10;
    }

}
}
