#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00459140
    int GameStateStructures::calculateTaxBribeExpenseForPlayer(int playerIndex, int taxStep, int currentPopulation)
    {
        int _taxIncome = ((5 - taxStep) * currentPopulation) / 2;
        if (this->playerDataArray[playerIndex].currentResources[0xf] <= 0) {
            _taxIncome = 0;
        }
        return _taxIncome;
    }

}
}
