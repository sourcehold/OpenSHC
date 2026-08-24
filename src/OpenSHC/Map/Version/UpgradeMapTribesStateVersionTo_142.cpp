#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"



#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {

using OpenSHC::Map::Units::SomeTribeBehaviorType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00523E00
void Version::UpgradeMapTribesStateVersionTo_142()

{
short *psVar1;

psVar1 = &DAT_TribesState::instance.tribes[1].attackWave;
do {
if ((psVar1[-0x13e] != 0) && (*psVar1 < 1)) {
psVar1[-0x136] = ((SomeTribeBehaviorType)0);
}
psVar1 = psVar1 + 0x19a;
} while ((int)psVar1 < 0x176261c);
return;
}


}
}