#include "OpenSHC/Map/Units/UnitsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0052F070
void UnitsState::makeUnitStopWalkingByClearingPathProgressState(int unitID)

{
this->units[unitID].currentIndexInPathPlan = 0;
this->units[unitID].totalSizeOfPathPlan = 0;
this->units[unitID].unknownMovementRelated_0x2d2 = 0;
this->units[unitID].climbDataID = 0;
return;
}


}
}
}