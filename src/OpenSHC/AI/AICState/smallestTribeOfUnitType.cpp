#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC990
    int AICState::smallestTribeOfUnitType(int playerID, AIVUnitType unitType)
    {
        int i = 0;
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL) {
            return 0;
        }

        int count = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[unitType];
        int smallestTribeID = 0;
        int smallestIndex = 0;
        int smallestSize = 1000;
        if (count > (int)this->aics[DAT_GameState::instance.playerDataArray[playerID].aiType - 1].defWallPatrolGroups
            && (unitType == 8 || unitType == 10 || unitType == 17)) {
            count = (int)this->aics[DAT_GameState::instance.playerDataArray[playerID].aiType - 1].defWallPatrolGroups;
        }

        int offset = DAT_SkirmishDefinedData::instance.AITribeIDOffsetForAIVUnitType[unitType];
        for (;; i++) {
            if (i >= count) {
                if (smallestTribeID == 0) {
                    return 0;
                }
                break;
            }
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[offset + i];
            if (tribeID == 0
                || DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[offset + i]) {
                smallestTribeID = MACRO_CALL_MEMBER(
                    Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                smallestIndex = i;
                break;
            }
            if (DAT_TribesState::instance.tribes[tribeID].size < smallestSize) {
                smallestSize = DAT_TribesState::instance.tribes[tribeID].size;
                smallestTribeID = tribeID;
                smallestIndex = i;
            }
        }

        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[offset + smallestIndex] = (short)smallestTribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[offset + smallestIndex]
            = DAT_TribesState::instance.tribes[smallestTribeID].uid;
        return smallestTribeID;
    }
}
}
