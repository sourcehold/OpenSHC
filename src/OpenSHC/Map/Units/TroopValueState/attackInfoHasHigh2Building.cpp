#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/AttackInfoSubArrayElement1.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::Map::AttackInfoSubArrayElement1;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0051AC80
BOOLEnum TroopValueState::attackInfoHasHigh2Building(int buildingID)

{
AttackInfoSubArrayElement1 * piVar1;

piVar1 = &this->attackInfo.high2ValuesArray[0];
do {
if (buildingID == piVar1->buildingID) {
return TRUE;
}
piVar1 = piVar1 + 4;
} while ((int)piVar1 < 0x177aaf8);
return FALSE;
}


}
}
}