#include "OpenSHC/Game/GameStateStructures.func.hpp"





namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0045AF00
void GameStateStructures::resetSomethingBuildingRelatedForAllPlayers()

{
int iVar1;
int playerID;

playerID = 1;
do {
iVar1 = 0;
do {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, this)(playerID, iVar1);
iVar1 = iVar1 + 1;
} while (iVar1 < 0x14);
playerID = playerID + 1;
} while (playerID < 9);
return;
}


}
}