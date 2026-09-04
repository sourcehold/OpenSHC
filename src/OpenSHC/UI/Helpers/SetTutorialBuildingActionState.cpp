#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_00df5588.hpp"
#include "OpenSHC/Globals/DAT_00df558c.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::Map::Buildings::BuildingType;


/* 
  Sets DAT_00df5588 (tutorial action type) and DAT_00df558c (building type) unless param_1 is 0xb
   and DAT_00df5588 is already 7 — in which case the update is skipped to avoid overwriting a
   pending state. Used to record which building-related action the player last performed for
   tutorial step evaluation.
   
   renamed by: Claude Sonnet 4.6
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004BC690
void Helpers::SetTutorialBuildingActionState(int param_1,BuildingType buildingType)

{
if ((param_1 != 0xb) || (DAT_00df5588::instance != 7)) {
DAT_00df5588::instance = param_1;
DAT_00df558c::instance = buildingType;
}
return;
}


}
}