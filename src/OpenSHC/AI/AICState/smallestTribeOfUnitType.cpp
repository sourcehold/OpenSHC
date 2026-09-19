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
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == AITA_NULL) {
            return 0;
        }

        int maxGroups = this->aics[DAT_GameState::instance.playerDataArray[playerID].aiType - 1].defWallPatrolGroups;
        int count = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[unitType];
        if (count > maxGroups && (unitType == 8 || unitType == 10 || unitType == 17)) {
            count = maxGroups;
        }

        int smallestTribeID = 0;
        int smallestIndex = 0;
        int smallestSize = 1000;
        int offset = DAT_SkirmishDefinedData::instance.AITribeIDOffsetForAIVUnitType[unitType];
        for (int i = 0; i < count; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[offset + i];
            if (tribeID == 0
                || DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[offset + i]) {
                // FIXME: The original binary jumps from here directly into the shared assignment code at the
                // end of the function, skipping the "smallestTribeID == 0" check. A goto reproduces this and
                // matches the assembly much better (~55% vs ~41%), but we avoid goto, so the assignment is
                // duplicated here.
                tribeID = MACRO_CALL_MEMBER(
                    Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[offset + i] = (short)tribeID;
                DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[offset + i]
                    = DAT_TribesState::instance.tribes[tribeID].uid;
                return tribeID;
            }
            if (DAT_TribesState::instance.tribes[tribeID].size < smallestSize) {
                smallestSize = DAT_TribesState::instance.tribes[tribeID].size;
                smallestTribeID = tribeID;
                smallestIndex = i;
            }
        }

        if (smallestTribeID == 0) {
            return 0;
        }

        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[offset + smallestIndex] = (short)smallestTribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[offset + smallestIndex]
            = DAT_TribesState::instance.tribes[smallestTribeID].uid;
        return smallestTribeID;
    }
}
}
