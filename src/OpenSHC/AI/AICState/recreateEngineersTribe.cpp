#include "../AICState.func.hpp"

#include "OpenSHC/AI/Tribes/AITribeIndex.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4630
    void AICState::recreateEngineersTribe(int playerID)
    {
        if (0 >= DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops) {
            return;
        }
        int const tribeID = DAT_GameState::instance.playerDataArray[playerID]
                                .aiTribeIDs[OpenSHC::AI::Tribes::AITI_BREACH_BASIC_07_01];
        if (tribeID != 0) {
            if (DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID]
                    .aiTribeUIDs[OpenSHC::AI::Tribes::AITI_BREACH_BASIC_07_01]) {
                DAT_GameState::instance.playerDataArray[playerID]
                    .aiTribeIDs[OpenSHC::AI::Tribes::AITI_BREACH_BASIC_07_01] = 0;
            }
        }
        MACRO_CALL_MEMBER(AICState_Func::addEngineersToTribe, this)(playerID);
    }
}
}
