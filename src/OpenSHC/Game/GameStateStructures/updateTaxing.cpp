#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045BF50
    void GameStateStructures::updateTaxing()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            if ((this->playerDataArray[playerID].keep.id > 0)
                && (this->playerDataArray[playerID].campground.id > 0)) {
                if (this->playerDataArray[playerID].taxesSetting < 3) {
                    this->playerDataArray[playerID].taxBribeMonthlyAccumulator
                        = this->playerDataArray[playerID].taxBribeMonthlyAccumulator
                        + MACRO_CALL_MEMBER(
                            OpenSHC::Game::GameStateStructures_Func::calculateTaxBribeExpenseForPlayer, this)(playerID,
                            this->playerDataArray[playerID].taxesSetting,
                            this->playerDataArray[playerID].currentPopulation);
                } else if (this->playerDataArray[playerID].taxesSetting > 3) {
                    this->playerDataArray[playerID].taxIncomeMonthlyAccumulator
                        = this->playerDataArray[playerID].taxIncomeMonthlyAccumulator
                        + MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateTaxIncomeForPlayer, this)(
                            playerID, this->playerDataArray[playerID].taxesSetting,
                            this->playerDataArray[playerID].currentPopulation);
                }
                if (this->mapAndTime.monthChanged != 0) {
                    this->playerDataArray[playerID].taxBribeMonthlyAccumulator
                        = this->playerDataArray[playerID].taxBribeMonthlyAccumulator / 10;
                    this->playerDataArray[playerID].taxIncomeMonthlyAccumulator
                        = this->playerDataArray[playerID].taxIncomeMonthlyAccumulator / 10;
                    this->playerDataArray[playerID].currentResources[0xf]
                        = this->playerDataArray[playerID].currentResources[0xf]
                        + this->playerDataArray[playerID].taxIncomeMonthlyAccumulator;
                    DAT_GameSynchronyState::instance.finalResults.finalGold[playerID]
                        = DAT_GameSynchronyState::instance.finalResults.finalGold[playerID]
                        + this->playerDataArray[playerID].taxIncomeMonthlyAccumulator;
                    this->playerDataArray[playerID].currentResources[0xf]
                        = this->playerDataArray[playerID].currentResources[0xf]
                        - this->playerDataArray[playerID].taxBribeMonthlyAccumulator;
                    if (this->playerDataArray[playerID].currentResources[0xf] < 0) {
                        this->playerDataArray[playerID].currentResources[0xf] = 0;
                    }
                    this->playerDataArray[playerID].lastMonthsBribeTax
                        = this->playerDataArray[playerID].taxBribeMonthlyAccumulator;
                    this->playerDataArray[playerID].lastMonthsIncomeTax
                        = this->playerDataArray[playerID].taxIncomeMonthlyAccumulator;
                    this->playerDataArray[playerID].taxIncomeMonthlyAccumulator = 0;
                    this->playerDataArray[playerID].taxBribeMonthlyAccumulator = 0;
                    this->playerDataArray[playerID].beforeLastMonthsGold
                        = this->playerDataArray[playerID].lastMonthsGold;
                    this->playerDataArray[playerID].lastMonthsGold
                        = (short)this->playerDataArray[playerID].currentResources[0xf];
                    this->playerDataArray[playerID].marketGold = 0;
                }
            }
        }
    }
}
}
