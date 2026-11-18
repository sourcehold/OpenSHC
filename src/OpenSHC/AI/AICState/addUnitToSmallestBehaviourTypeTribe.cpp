#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/AI/AIUnitBehaviourType.hpp"
#include "OpenSHC/AI/Tribes/AITribeIndex.hpp"

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
        int firstSlot
            = DAT_SkirmishDefinedData::instance.AIUnitBehaviourTypeMapping[aiUnitBehaviourType - AIUBT_ENGINEERING];
        int selectedTribeID = 0;
        int selectedSlot = 0;
        int smallestSize = 1000;
        int groupsCount;
        switch (firstSlot) {
        case OpenSHC::AI::Tribes::AITI_BREACH_BASIC_05_01:
            groupsCount = this->aics[aicIndex].AttUnitPatrolGroupsCount;
            break;
        case OpenSHC::AI::Tribes::AITI_BREACH_08_01:
            groupsCount = this->aics[aicIndex].AttUnitBackupGroupsCount;
            break;
        case OpenSHC::AI::Tribes::AITI_BREACH_10_01:
            groupsCount = this->aics[aicIndex].AttUnitSiegeDefGroupsCount;
            break;
        case OpenSHC::AI::Tribes::AITI_BREACH_11_01:
            groupsCount = this->aics[aicIndex].AttMainGroupsCount;
            break;
        default:
            groupsCount = 1;
            break;
        }
        if (groupsCount < 1)
            groupsCount = 1;

        int resultTribeID = 0;
        if (groupsCount == 1) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[firstSlot];
            if (tribeID != 0
                && DAT_TribesState::instance.tribes[tribeID].uid
                    == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[firstSlot])
                return tribeID;
            resultTribeID
                = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);
        } else {
            // groupsCount becomes the end slot: the original keeps the bound in the register of groupsCount
            groupsCount += firstSlot;
            for (int slot = firstSlot; slot < groupsCount; ++slot) {
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
            // the loop's choice is copied out here, tribe and slot alike: the original reads both back from the
            // stack on the loop's exit, and the stores below index by firstSlot
            resultTribeID = selectedTribeID;
            firstSlot = selectedSlot;
        }
        if (resultTribeID <= 0)
            return 0;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[firstSlot] = resultTribeID;
        DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[firstSlot]
            = DAT_TribesState::instance.tribes[resultTribeID].uid;
        return resultTribeID;
    }
}
}
