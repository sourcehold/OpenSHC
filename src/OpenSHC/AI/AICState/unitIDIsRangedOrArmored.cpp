#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishDefinedData.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

using OpenSHC::Game::Skirmish::SkirmishDefinedData;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004CC8D0
undefined4 AICState::unitIDIsRangedOrArmored(int unitID)

{
SkirmishDefinedData *pSVar1;

pSVar1 = DAT_SkirmishDefinedData::ptr;
do {
if (pSVar1->RangedAndArmoredUnits[0] == (int)(short)DAT_UnitsState::instance.units[unitID].unitType) {
return(undefined4)( 1);
}
pSVar1 = (SkirmishDefinedData *)(pSVar1->RangedAndArmoredUnits + 1);
} while ((int)pSVar1 < 0xb3eb50);
return(undefined4)( 0);
}


}
}