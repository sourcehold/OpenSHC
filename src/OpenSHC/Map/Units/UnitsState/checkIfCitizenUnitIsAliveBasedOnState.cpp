#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Map::Units::States::UnitStateShort;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00530FD0
BOOLEnum UnitsState::checkIfCitizenUnitIsAliveBasedOnState(int param_1)

{
UnitStateShort _state;

_state = this->units[param_1].state.generic;
if ((0x6e < (short)_state) && ((short)_state < 0x75)) {
return TRUE;
}
return FALSE;
}


}
}
}