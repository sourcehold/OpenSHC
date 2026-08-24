#include "OpenSHC/Map/Units/UnitsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0052FBB0
undefined4 UnitsState::standUpIfSeated(int param_1)

{
if (this->units[param_1].seated == 0) {
return(undefined4)( 0);
}
this->units[param_1].substate = 100;
this->units[param_1].animationCycleNumber = 0;
return(undefined4)( 1);
}


}
}
}