#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4630
    void AICState::recreateEngineersTribe(int playerID)
    {
        if (0 < DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops) {
            int _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0x12];
            if ((_tribeID != 0)
                && (DAT_TribesState::instance.tribes[_tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0x12])) {
                DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0x12] = 0;
            }
            MACRO_CALL_MEMBER(AICState_Func::addEngineersToTribe, this)(playerID);
        }
    }
}
}
