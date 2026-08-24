#include "OpenSHC/Game/GameStateStructures.func.hpp"





namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00459170
int GameStateStructures::getNumberToDisplayPlayerTaxIncome(int playerIndex,int taxStep,int currentPopulation)

{
int iVar1;

iVar1 = 0;
if (3 < taxStep) {
iVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::calculateTaxIncomeForPlayer, this)(playerIndex, taxStep, currentPopulation);
iVar1 = iVar1 * 4;
}
return iVar1 / 10;
}


}
}