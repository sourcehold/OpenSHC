#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/State/UnitSelectionHotKeyEntry.hpp"





namespace OpenSHC {
namespace Game {

using OpenSHC::Game::State::UnitSelectionHotKeyEntry;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00459BB0
void GameStateStructures::clearTribeHotKey(int hotkeyID)

{
UnitSelectionHotKeyEntry *pUVar1;
int iVar2;

pUVar1 = this->hotkeyTribes + hotkeyID;
iVar2 = 2500;
do {
pUVar1->units[0].id = -1;
pUVar1->units[0].uid = -1;
pUVar1 = (UnitSelectionHotKeyEntry *)(pUVar1->units + 1);
iVar2 = iVar2 + -1;
} while (iVar2 != 0);
return;
}


}
}