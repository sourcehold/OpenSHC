#include "OpenSHC/Game/GameStateStructures.func.hpp"





namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004591B0
int GameStateStructures::getNumberToDisplayBribeIncome(int playerIndex,int taxStep,int currentPopulation)

{
int iVar1;

iVar1 = 0;
if (taxStep < 3) {
iVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateTaxBribeExpenseForPlayer, this)(playerIndex, taxStep, currentPopulation);
iVar1 = iVar1 * 4;
}
return iVar1 / 10;
}


}
}