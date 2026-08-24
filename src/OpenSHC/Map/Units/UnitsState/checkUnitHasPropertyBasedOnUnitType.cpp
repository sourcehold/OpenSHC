#include "OpenSHC/Map/Units/UnitsState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0052F0A0
int UnitsState::checkUnitHasPropertyBasedOnUnitType(int unitID,int property)

{
return DAT_UnitPropertiesDefinedData::instance.UnitClimbStateFlags[property]
[(short)this->units[unitID].unitType];
}


}
}
}