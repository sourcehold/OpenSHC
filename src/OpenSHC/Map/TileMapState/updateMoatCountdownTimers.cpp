#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Moat.hpp"





namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Moat;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00500640
void TileMapState::updateMoatCountdownTimers()

{
Moat * _pMoats;
int iVar1;

MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::recountTotalOwnedMoats, this)();
iVar1 = 0;
/* 
  DAT_TotalOwnedMoats
 */

if (0 < this->currentMoatCount) {
/* 
  SEC_MoatArray[0].field11_0xf
 */

_pMoats = &this->moats[0];
do {
if ((_pMoats->owner != 0) && ('\0' < (char)_pMoats->someCountDown)) {
_pMoats->someCountDown = _pMoats->someCountDown - 1;
}
iVar1 = iVar1 + 1;
_pMoats = _pMoats + 0x10;
} while (iVar1 < this->currentMoatCount);
}
return;
}


}
}