#include "OpenSHC/Map/Units/UnitsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00533C70
void UnitsState::changeDestinationByLeftover(int unitID)

{
short _leftover;

_leftover = this->units[unitID].leftover;
if (0 < _leftover) {
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, this)(unitID, (int)((int)(_leftover)));
}
return;
}


}
}
}