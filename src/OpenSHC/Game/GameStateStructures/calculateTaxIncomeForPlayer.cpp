#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      Note that this income gets divided by 10 before being added to the players current gold   decompilerscript:
      committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459080
    int GameStateStructures::calculateTaxIncomeForPlayer(int playerIndex, int taxStep, int currentPeasants)
    {
        int taxIncome = ((taxStep - 1) * currentPeasants) / 2;
        /*
          Is Skirmish
         */
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            return taxIncome;
        }
        /*
          Is NOT Player
         */
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerIndex] == -1) {
            /*
              Is AI
             */
            if (DAT_GameSynchronyState::instance.currentAIArray[playerIndex] == 0) {
                return taxIncome;
            }
            /*
              balance is towards ai players: multiply by 150, divide by 100
             */
            if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance == 4) {
                return (taxIncome * 150) / 100;
            }
            /*
              multiply by 250, divide by 100
             */
            if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance == 5) {
                return (taxIncome * 250) / 100;
            }
            return taxIncome;
        }
        /*
          balance is towards human players: multiply by 150, divide by 100
         */
        if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance == 1) {
            return (taxIncome * 150) / 100;
        }
        /*
          multiply by 120, divide by 100
         */
        if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance == 2) {
            taxIncome = (taxIncome * 120) / 100;
        }
        return taxIncome;
    }
}
}
