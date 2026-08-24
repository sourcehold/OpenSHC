#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicStateShort.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Units::UnitLogicStateShort;
using OpenSHC::Map::Units::UnitLogicState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0053B310
void Version::UpgradeMapUnitsTo_114()

{
int *piVar1;

piVar1 = &DAT_UnitsState::instance.units[1].calculatedOwnerPlayerIndex;
DAT_CurrentUnitSlotID::instance = 2500;
do {
if (*(UnitLogicStateShort *)(piVar1 + 0x1f) == OpenSHC::Map::Units::ULS_NORMAL) {
*piVar1 = 0;
}
piVar1 = piVar1 + 0x124;
} while ((int)piVar1 < 0x165139c);
return;
}


}
}