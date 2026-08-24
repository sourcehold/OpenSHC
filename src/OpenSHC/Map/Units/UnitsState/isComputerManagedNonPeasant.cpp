#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"



#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Map::Units::UnitTypeShort;
using OpenSHC::Map::Units::UnitType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00530080
BOOLEnum UnitsState::isComputerManagedNonPeasant(int param_1)

{
UnitTypeShort UVar1;

UVar1 = this->units[param_1].unitType;
if (UVar1 == OpenSHC::Map::Units::UT_PEASANT) {
return FALSE;
}
return (uint)(DAT_UnitPropertiesDefinedData::instance.COMPUTER_MANAGED[(short)UVar1] != 0);
}


}
}
}