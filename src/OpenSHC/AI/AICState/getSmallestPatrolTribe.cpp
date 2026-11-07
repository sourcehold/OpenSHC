#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeIndex.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCAF0
    int AICState::getSmallestPatrolTribe(int playerID, int tribeCount)
    {
        int i = 0;
        int selectedTribeID = 0;
        int selectedIndex = 0;
        int lowestSize = 1000;

        for (;; i++) {
            if (i >= tribeCount) {
                if (selectedTribeID == 0)
                    return 0;
                break;
            }

            int const tribeID
                = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[OpenSHC::AI::Tribes::AITI_PAT_Unk + i];
            if (tribeID == 0
                || DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID]
                        .aiTribeUIDs[i + OpenSHC::AI::Tribes::AITI_PAT_Unk]) {
                selectedTribeID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                selectedIndex = i;
                break;
            }

            if (DAT_TribesState::instance.tribes[tribeID].size < lowestSize) {
                lowestSize = DAT_TribesState::instance.tribes[tribeID].size;
                selectedTribeID = tribeID;
                selectedIndex = i;
            }
        }

        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[selectedIndex + OpenSHC::AI::Tribes::AITI_PAT_Unk]
            = selectedTribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[selectedIndex + OpenSHC::AI::Tribes::AITI_PAT_Unk]
            = DAT_TribesState::instance.tribes[selectedTribeID].uid;
        return selectedTribeID;
    }
}
}
