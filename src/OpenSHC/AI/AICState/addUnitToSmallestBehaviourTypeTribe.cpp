#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CCD20
    int AICState::addUnitToSmallestBehaviourTypeTribe(
        undefined4 playerID, undefined4 unitID, undefined4 aiUnitBehaviourType)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return 0;

        int aicIndex = aiType - 1;
        int tribeType = DAT_SkirmishDefinedData::instance.AIUnitBehaviourTypeMapping[aiUnitBehaviourType - 10];
        int groupsCount;
        switch (tribeType) {
        case 15:
            groupsCount = this->aics[aicIndex].AttUnitPatrolGroupsCount;
            break;
        case 186:
            groupsCount = this->aics[aicIndex].AttUnitBackupGroupsCount;
            break;
        case 190:
            groupsCount = this->aics[aicIndex].AttUnitSiegeDefGroupsCount;
            break;
        case 192:
            groupsCount = this->aics[aicIndex].AttMainGroupsCount;
            break;
        default:
            groupsCount = 1;
            break;
        }

        int selectedTribeID = 0;
        int selectedSlot = 0;
        if (groupsCount <= 1) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[tribeType];
            if (tribeID != 0
                && DAT_TribesState::instance.tribes[tribeID].uid
                    == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[tribeType])
                return tribeID;
            selectedTribeID
                = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
            selectedSlot = tribeType;
        } else {
            int smallestSize = 1000;
            for (int slot = tribeType; slot < tribeType + groupsCount; slot++) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[slot];
                if (tribeID == 0
                    || DAT_TribesState::instance.tribes[tribeID].uid
                        != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[slot]) {
                    selectedTribeID = MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
                    selectedSlot = slot;
                    break;
                }
                if (DAT_TribesState::instance.tribes[tribeID].size < smallestSize) {
                    smallestSize = DAT_TribesState::instance.tribes[tribeID].size;
                    selectedTribeID = tribeID;
                    selectedSlot = slot;
                }
            }
        }
        if (selectedTribeID <= 0)
            return 0;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[selectedSlot] = selectedTribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[selectedSlot]
            = DAT_TribesState::instance.tribes[selectedTribeID].uid;
        return selectedTribeID;
    }
}
}
