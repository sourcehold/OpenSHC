#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2870
    void AICState::sendTribeAtOffset1ToCampfire(int playerID)
    {
        int _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[1];
        if ((0 < _tribeID) &&
            (DAT_TribesState::instance.tribes[_tribeID].uid == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[1])) {
            MACRO_CALL_MEMBER(AICState_Func::sendUnitsToCampfire, this)(_tribeID, playerID);
        }
    }
}
}
