#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::Map::Units::UnitsState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0053B8B0
UnitsState * UnitsState::constructUnitsState()

{
this->creationTime = timeGetTime();
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearAllUnits, this)();
this->lastSelectedUnitID = 0;
this->unknownInitially0_01 = 0;
this->lostChimps = 0;
this->maxUnitCount = 2500;
return this;
}


}
}
}