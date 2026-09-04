#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace AI {

using OpenSHC::Game::Player::PlayerID;
using OpenSHC::AI::AITypeInt;
using OpenSHC::AI::AIType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004CB180
int AICState::aiFarmChoice(PlayerID playerID)

{
AITypeInt AVar1;

AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;
if (AVar1 == OpenSHC::AI::AIT_NULL) {
return 0;
}
/* 
  ugly because EAX is always 1 or higher
 */

return *(int *)((int)DAT_EntityState::instance.seagullArray +
(AVar1 * 0xa9 + DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex) * 4 + 0x24a0);
}


}
}