#include "OpenSHC/Map/TileMapState.func.hpp"





namespace OpenSHC {
namespace Map {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x005000A0
void TileMapState::recountTotalOwnedMoats()

{
int iVar1;
byte *pbVar2;

this->currentMoatCount = 0;
iVar1 = 1;
pbVar2 = &this->moats[1].owner;
do {
if (*pbVar2 != 0) {
this->currentMoatCount = iVar1 + 1;
}
iVar1 = iVar1 + 1;
pbVar2 = pbVar2 + 0x10;
} while (iVar1 < 16000);
return;
}


}
}