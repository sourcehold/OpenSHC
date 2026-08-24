#include "OpenSHC/Map/Units/TribesState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x005224E0
int TribesState::setWhetherTribeContainsAnyUnits(int tribeID)

{
int iVar1;
short *psVar2;

iVar1 = 0;
psVar2 = this->tribes[tribeID].unitSelectionBitMasked;
do {
if (*psVar2 != 0) {
this->tribes[tribeID].highestID = (short)iVar1;
return iVar1;
}
iVar1 = iVar1 + 1;
psVar2 = psVar2 + 1;
} while (iVar1 < 200);
return iVar1;
}


}
}
}