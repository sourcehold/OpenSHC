#include "OpenSHC/Map/Units/TroopValueState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00518350
undefined4 TroopValueState::isAttackWaveComplete()

{
int iVar1;

iVar1 = 0;
while ((this->attackInfo.nof_tribes[iVar1] == 0 ||
(this->attackInfo.value3Array01[iVar1] == 6))) {
iVar1 = iVar1 + 1;
if (0x31 < iVar1) {
return(undefined4)( 1);
}
}
return(undefined4)( 0);
}


}
}
}