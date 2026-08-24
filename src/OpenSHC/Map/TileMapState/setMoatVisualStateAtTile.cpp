#include "OpenSHC/Map/TileMapState.func.hpp"





namespace OpenSHC {
namespace Map {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00500720
void TileMapState::setMoatVisualStateAtTile(int tile,undefined4 zeroOrTwo)

{
int iVar1;

iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(tile);
if (iVar1 != 0) {
this->moats[iVar1].zeroOrTwo = (short)zeroOrTwo;
}
return;
}


}
}