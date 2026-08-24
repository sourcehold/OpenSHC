#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Map::Units::States::UnitState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0053CAC0
BOOLEnum Units::UpdateWorker_ConsiderTakingABreakUnk(int unitID)

{
BOOLEnum BVar1;

BVar1 = MACRO_CALL(OpenSHC::Map::Units_Func::ConsiderHavingABreakNowUnk)(unitID, (UnitState)((int)((int)(short)DAT_UnitsState::instance.units[unitID].state.generic)));
return BVar1;
}


}
}