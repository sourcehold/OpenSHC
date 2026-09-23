#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2830
    void AICState::ifHasTribe0SendUnitsToKeep(int playerID)
    {
        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0];
        if (tribeID <= 0)
            return;
        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0])
            return;

        MACRO_CALL_MEMBER(AICState_Func::sendUnitsToKeep, this)(tribeID, playerID);
    }
}
}
