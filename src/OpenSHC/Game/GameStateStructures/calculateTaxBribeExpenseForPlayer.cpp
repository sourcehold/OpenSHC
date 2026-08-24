#include "OpenSHC/Game/GameStateStructures.func.hpp"





namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00459140
int GameStateStructures::calculateTaxBribeExpenseForPlayer(int playerIndex,int taxStep,int currentPopulation)

{
int _taxIncome;

_taxIncome = ((5 - taxStep) * currentPopulation) / 2;
if (this->playerDataArray[playerIndex].currentResources[0xf] < 1) {
_taxIncome = 0;
}
return _taxIncome;
}


}
}