#include "OpenSHC/Map/Units/TroopValueState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0051B680
void TroopValueState::clearAIInfoLayerOutsideStartZone()

{
int iVar1;
int iVar2;

iVar1 = this->attackInfo.startCon;
iVar2 = 0;
do {
if ((DAT_TileMapState::instance.AIInfoLayer[iVar2] != '\0') &&
((short)DAT_TileMapState::instance.PathConnectionLayer[iVar2] != iVar1)) {
DAT_TileMapState::instance.AIInfoLayer[iVar2] = '\0';
}
iVar2 = iVar2 + 1;
} while (iVar2 < 0x13a10);
return;
}


}
}
}