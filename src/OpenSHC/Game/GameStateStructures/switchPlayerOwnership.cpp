#include "../GameStateStructures.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045B460
    void GameStateStructures::switchPlayerOwnership(int playerID)
    {
        for (int fromPlayerID = 1; fromPlayerID < 9; ++fromPlayerID) {
            if (fromPlayerID != playerID) {
                MACRO_CALL_MEMBER(GameStateStructures_Func::changePlayerOwnership, this)(fromPlayerID, playerID);
            }
        }
        MACRO_CALL_MEMBER(AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
    }

}
}
