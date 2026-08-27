#include "../GameStateStructures.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045B460
    void GameStateStructures::switchPlayerOwnership(int playerID)
    {
        for (int fromPlayer = 1; fromPlayer < 9; fromPlayer++) {
            if (fromPlayer != playerID) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::changePlayerOwnership, this)(
                    fromPlayer, playerID);
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
    }

}
}
