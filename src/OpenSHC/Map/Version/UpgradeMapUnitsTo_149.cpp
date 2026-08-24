#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Units::Unit;
using OpenSHC::Map::Units::UnitLogicState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0053B570
void Version::UpgradeMapUnitsTo_149()

{
Unit * psVar1;

psVar1 = &DAT_UnitsState::instance.units[1];
DAT_CurrentUnitSlotID::instance = 0x9c4;
do {
if (psVar1->logicalState == OpenSHC::Map::Units::ULS_NORMAL) {
psVar1->shootBeforeStop = 0;
}
psVar1 = psVar1 + 0x248;
} while ((int)psVar1 < 0x1651764);
return;
}


}
}