#include "OpenSHC/Map/Trees.func.hpp"



#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"

namespace OpenSHC {
namespace Map {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004F28F0
void Trees::UpdateTree16()

{
int iVar1;
int iVar2;

iVar1 = DAT_CurrentTreeID::instance;
iVar2 = (DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].rng1 &7U) + 10;
DAT_LandscapeState::instance.trees[DAT_CurrentTreeID::instance].animationFrameUnk = iVar2;
DAT_LandscapeState::instance.trees[iVar1].animationFrame2Unk = iVar2;
return;
}


}
}