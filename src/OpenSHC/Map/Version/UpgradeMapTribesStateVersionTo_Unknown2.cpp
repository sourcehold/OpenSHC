#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"



#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00523EB0
void Version::UpgradeMapTribesStateVersionTo_Unknown2()

{
short *psVar1;
int tribeID;

tribeID = 1;
psVar1 = &DAT_TribesState::instance.tribes[1].tribeState;
do {
if (*psVar1 != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, DAT_TribesState::ptr)(tribeID);
}
psVar1 = psVar1 + 0x19a;
tribeID = tribeID + 1;
} while ((int)psVar1 < 0x17623a0);
return;
}


}
}