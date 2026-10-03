#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC910
    int AICState::createTribeForUnitType(int playerID, int unitSelectionTypeIndex)
    {
        int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[unitSelectionTypeIndex];
        if (tribeID != 0
            && DAT_TribesState::instance.tribes[tribeID].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[unitSelectionTypeIndex])
            return tribeID;

        tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[unitSelectionTypeIndex] = tribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[unitSelectionTypeIndex]
            = DAT_TribesState::instance.tribes[tribeID].uid;
        return tribeID;
    }
}
}
