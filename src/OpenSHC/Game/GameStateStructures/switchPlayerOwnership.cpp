#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/AI/AICState.func.hpp"



#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {
namespace Game {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0045B460
void GameStateStructures::switchPlayerOwnership(int playerID)

{
int fromPlayer;

fromPlayer = 1;
do {
if (fromPlayer != playerID) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::changePlayerOwnership, this)(fromPlayer, playerID);
}
fromPlayer = fromPlayer + 1;
} while (fromPlayer < 9);
MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
return;
}


}
}