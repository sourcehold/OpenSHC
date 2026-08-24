#include "OpenSHC/Map/Units/TribesState.func.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00523340
void TribesState::storeDeerXAndYinMapInfo(undefined4 x,undefined4 y)

{
short (*pasVar1) [2];

pasVar1 = DAT_GameState::instance.mapAndTime.deerSpawnLocationsXY;
do {
if ((*pasVar1)[0] == 0) {
(*pasVar1)[0] = (short)x;
(*pasVar1)[1] = (short)y;
}
pasVar1 = pasVar1 + 1;
} while ((int)pasVar1 < 0x117d1dc);
return;
}


}
}
}