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


// FUNCTION: STRONGHOLDCRUSADER 0x00501730
void Version::UpgradeMapLogicToVersion_147()

{
int _tile;

_tile = 0;
do {
if (156 < DAT_TileMapState::instance.DefaultHeightLayer[_tile]) {
DAT_TileMapState::instance.HeightLayer[_tile] =
DAT_TileMapState::instance.HeightLayer[_tile] + (156 - DAT_TileMapState::instance.DefaultHeightLayer[_tile])
;
DAT_TileMapState::instance.DefaultHeightLayer[_tile] = 156;
}
_tile = _tile + 1;
} while (_tile < 80400);
return;
}


}
}