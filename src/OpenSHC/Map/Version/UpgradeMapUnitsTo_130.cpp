#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Units::UnitTypeShort;
using OpenSHC::Map::Units::UnitLogicState;
using OpenSHC::Map::Units::UnitType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0053B530
void Version::UpgradeMapUnitsTo_130()

{
UnitTypeShort *pUVar1;

pUVar1 = &DAT_UnitsState::instance.units[1].unitType;
DAT_CurrentUnitSlotID::instance = 0x9c4;
do {
if ((pUVar1[-1] == OpenSHC::Map::Units::ULS_NORMAL) && (*pUVar1 == OpenSHC::Map::Units::UT_COW)) {
pUVar1[0x193] = 0;
}
pUVar1 = pUVar1 + 0x248;
} while ((int)pUVar1 < 0x165141a);
return;
}


}
}