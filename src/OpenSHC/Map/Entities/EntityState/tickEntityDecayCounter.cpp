#include "OpenSHC/Map/Entities/EntityState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Entities {




/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00401430
void EntityState::tickEntityDecayCounter(int param_1)

{
short sVar1;

sVar1 = this->entityArray[param_1].unkMinusOne;
if (0x1e < sVar1) {
this->entityArray[param_1].logicalState = 3;
return;
}
this->entityArray[param_1].unkMinusOne = sVar1 + 1;
return;
}


}
}
}