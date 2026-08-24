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


// FUNCTION: STRONGHOLDCRUSADER 0x0051ACB0
undefined4 TroopValueState::attackInfoHasArch2Building(int buildingID)

{
int *piVar1;

piVar1 = &this->attackInfo.arch2ValuesArray[0].buildingID;
do {
if (buildingID == *piVar1) {
return(undefined4)( 1);
}
piVar1 = piVar1 + 4;
} while ((int)piVar1 < 0x177e994);
return(undefined4)( 0);
}


}
}
}