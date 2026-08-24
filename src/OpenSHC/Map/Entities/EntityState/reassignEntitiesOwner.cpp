#include "OpenSHC/Map/Entities/EntityState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Entities {




/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00401AE0
void EntityState::reassignEntitiesOwner(int param_1,undefined4 param_2)

{
short *psVar1;
int iVar2;

psVar1 = &this->entityArray[1].owner;
iVar2 = 2999;
do {
if ((psVar1[-2] == 2) && (*psVar1 == param_1)) {
*psVar1 = (short)param_2;
}
psVar1 = psVar1 + 0x74;
iVar2 = iVar2 + -1;
} while (iVar2 != 0);
return;
}


}
}
}