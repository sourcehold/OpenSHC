#include "OpenSHC/Map/MapPropertiesState.func.hpp"





namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004B7890
undefined4 MapPropertiesState::mapHasCertainEvent()

{
int iVar1;
int *piVar2;

iVar1 = 0;
if (0 < this->eventsCount) {
piVar2 = &this->scenarioEvents[0].header.tl_type;
do {
if (*piVar2 == 1) {
return(undefined4)( 1);
}
iVar1 = iVar1 + 1;
piVar2 = piVar2 + 0x39;
} while (iVar1 < this->eventsCount);
}
return(undefined4)( 0);
}


}
}