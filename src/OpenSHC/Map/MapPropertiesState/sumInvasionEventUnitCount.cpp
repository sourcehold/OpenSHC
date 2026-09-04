#include "OpenSHC/Map/MapPropertiesState.func.hpp"





namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004BBA20
void MapPropertiesState::sumInvasionEventUnitCount()

{
int *piVar1;
int *piVar2;

this->DAT_InvasionEventItemUnitCountSum = 0;
piVar1 = this->invasionEventContent.unitCountsPerUnitType + 3;
do {
piVar2 = piVar1 + 5;
this->DAT_InvasionEventItemUnitCountSum =
this->DAT_InvasionEventItemUnitCountSum +
piVar1[-3] + piVar1[-2] + piVar1[-1] + piVar1[1] + *piVar1;
piVar1 = piVar2;
} while ((int)piVar2 < 0x1667ebc);
return;
}


}
}