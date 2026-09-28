#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00459080
    int GameStateStructures::calculateTaxIncomeForPlayer(int playerIndex, int taxStep, int currentPeasants)
    {
        int taxIncome = ((taxStep - 1) * currentPeasants) / 2;
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerIndex] == -1) {
                if (DAT_GameSynchronyState::instance.currentAIArray[playerIndex] != 0) {
                    if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance != 4) {
                        if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance == 5) {
                            return (taxIncome * 250) / 100;
                        }
                        return taxIncome;
                    }
                    return (taxIncome * 150) / 100;
                }
            } else {
                if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance == 1) {
                    return (taxIncome * 150) / 100;
                }
                if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance == 2) {
                    taxIncome = (taxIncome * 120) / 100;
                }
            }
        }
        return taxIncome;
    }

}
}
