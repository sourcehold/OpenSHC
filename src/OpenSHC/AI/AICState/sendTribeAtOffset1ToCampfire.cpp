#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2870
    void AICState::sendTribeAtOffset1ToCampfire(int playerID)
    {
        int const tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[1];
        if (tribeID <= 0)
            return;
        if (DAT_TribesState::instance.tribes[tribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[1])
            return;
        MACRO_CALL_MEMBER(AICState_Func::sendUnitsToCampfire, this)(tribeID, playerID);
    }
}
}
