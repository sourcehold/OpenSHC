#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00519960
BOOLEnum TroopValueState::getTileInTargetedBuildingTiles(int tile)

{
int _index;

_index = 0;
if (0 < this->attackInfo.targetedBuildingTilesArraySize) {
do {
if (this->attackInfo.targetedBuildingTilesArray[_index] == tile) {
return TRUE;
}
_index = _index + 1;
} while (_index < this->attackInfo.targetedBuildingTilesArraySize);
}
return FALSE;
}


}
}
}