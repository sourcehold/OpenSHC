#include "OpenSHC/Map/Units/UnitsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00535190
void UnitsState::deselectUnit(int unitID)

{
if (this->units[unitID].isSelected != 0) {
this->units[unitID].isSelected = 0;
this->totalUnitsInSelection = this->totalUnitsInSelection + -1;
}
return;
}


}
}
}