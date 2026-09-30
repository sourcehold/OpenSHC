#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00459140
    int GameStateStructures::calculateTaxBribeExpenseForPlayer(int playerIndex, int taxStep, int currentPopulation)
    {
        int bribeExpense = ((5 - taxStep) * currentPopulation) / 2;
        if (this->playerDataArray[playerIndex].currentResources[Resources::RT_GOLD] <= 0) {
            bribeExpense = 0;
        }
        return bribeExpense;
    }

}
}
