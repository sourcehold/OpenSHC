#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCAF0
    int AICState::getSmallestPatrolTribe(int playerID, int tribeCount)
    {
        int selectedTribeID = 0;
        int selectedIndex = 0;
        int lowestSize = 1000;

        for (int i = 0; i < tribeCount; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[170 + i];
            if (tribeID == 0
                || DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[i + 170]) {
                selectedTribeID
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(
                        playerID);
                selectedIndex = i;
                break;
            }

            if (DAT_TribesState::instance.tribes[tribeID].size < lowestSize) {
                lowestSize = DAT_TribesState::instance.tribes[tribeID].size;
                selectedTribeID = tribeID;
                selectedIndex = i;
            }
        }

        if (selectedTribeID == 0)
            return 0;

        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[selectedIndex + 170] = selectedTribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[selectedIndex + 170]
            = DAT_TribesState::instance.tribes[selectedTribeID].uid;
        return selectedTribeID;
    }
}
}
