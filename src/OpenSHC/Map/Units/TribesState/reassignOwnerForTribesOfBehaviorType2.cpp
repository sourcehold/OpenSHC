#include "OpenSHC/Map/Units/TribesState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00521210
void TribesState::reassignOwnerForTribesOfBehaviorType2(int param_1,int param_2)

{
int *piVar1;

piVar1 = &this->tribes[1].owner;
do {
if ((*(short *)(piVar1 + 5) == 2) && (*piVar1 == param_1)) {
*piVar1 = param_2;
}
piVar1 = piVar1 + 0xcd;
} while ((int)piVar1 < 0x176238c);
return;
}


}
}
}