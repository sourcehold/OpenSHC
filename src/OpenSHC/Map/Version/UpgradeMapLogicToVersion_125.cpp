#include "OpenSHC/Map/Version.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x005011C0
void Version::UpgradeMapLogicToVersion_125()

{
int iVar1;

iVar1 = 0;
do {
if (DAT_TileMapState::instance.HeightLayer[iVar1] == 80) {
DAT_TileMapState::instance.Logic2Layer[iVar1] = 4;
}
else if (DAT_TileMapState::instance.HeightLayer[iVar1] == 130) {
DAT_TileMapState::instance.Logic2Layer[iVar1] = 8;
}
iVar1 = iVar1 + 1;
} while (iVar1 < 0x13a10);
return;
}


}
}