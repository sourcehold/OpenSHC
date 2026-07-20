#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC960
    int AICState::createTribeForUnitType(int playerID, int unitSelectionTypeIndex)
    {
        short* psVar1 = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + unitSelectionTypeIndex;
        int _tribeID = (int)*psVar1;
        if ((_tribeID == 0)
            || (DAT_TribesState::instance.tribes[_tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[unitSelectionTypeIndex])) {
            _tribeID
                = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
            int _tribeUID = DAT_TribesState::instance.tribes[_tribeID].uid;
            *psVar1 = (short)_tribeID;
            DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[unitSelectionTypeIndex] = _tribeUID;
        }
        return _tribeID;
    }
}
}
