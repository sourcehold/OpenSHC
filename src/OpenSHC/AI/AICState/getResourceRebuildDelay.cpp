#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace AI {

using OpenSHC::AI::AITypeInt;
using OpenSHC::AI::AIType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004CB150
int AICState::getResourceRebuildDelay(int param_1)

{
AITypeInt AVar1;

AVar1 = DAT_GameState::instance.playerDataArray[param_1].aiType;
if (AVar1 == OpenSHC::AI::AIT_NULL) {
return 0;
}
/* 
  access resourceBuildDelay
 */

return *(int *)((int)DAT_EntityState::instance.seagullArray + AVar1 * 0x2a4 + 0x24ec);
}


}
}