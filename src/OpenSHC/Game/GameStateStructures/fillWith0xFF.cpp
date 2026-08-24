#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/GameStateStructures.hpp"





namespace OpenSHC {
namespace Game {

using OpenSHC::Game::GameStateStructures;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00459BE0
void GameStateStructures::fillWith0xFF()

{
GameStateStructures *pGVar1;
int iVar2;
int iVar3;

pGVar1 = this;
iVar3 = 10;
do {
iVar2 = 0x9c4;
do {
pGVar1->hotkeyTribes[0].units[0].id = -1;
pGVar1->hotkeyTribes[0].units[0].uid = -1;
pGVar1 = (GameStateStructures *)(pGVar1->hotkeyTribes[0].units + 1);
iVar2 = iVar2 + -1;
} while (iVar2 != 0);
iVar3 = iVar3 + -1;
} while (iVar3 != 0);
return;
}


}
}