#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitStateUnion.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::Map::Units::States::UnitStateUnion;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00533F90
void UnitsState::saveUnitStateBeforeInterruption(int param_1)

{
UnitStateUnion UVar1;

UVar1 = this->units[param_1].state;
this->units[param_1].tunnelerFinishedDigging = 5;
this->units[param_1].state_3 = UVar1;
return;
}


}
}
}