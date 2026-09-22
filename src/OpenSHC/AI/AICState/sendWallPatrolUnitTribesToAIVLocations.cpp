#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/AI/AIVUnitTypeInt.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeMaxLocationPair.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::AI::AIVUnitTypeInt;
    using OpenSHC::AI::Tribes::AIVUnitTypeMaxLocationPair;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D4340
    void AICState::sendWallPatrolUnitTribesToAIVLocations(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }

        int aicIndex = aiType - 1;
        BOOLEnum enclosed = MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(playerID);

        for (int i = 0; i < 3; i++) {
            int count = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount
                            [DAT_SkirmishDefinedData::instance.MaxAIVLocationForPatrolUnits[i].aivUnitType];
            int groups = count;
            if (count > this->aics[aicIndex].defWallPatrolGroups) {
                groups = this->aics[aicIndex].defWallPatrolGroups;
            }
            if (groups <= 0) {
                continue;
            }

            int stepSize = count / groups;
            if (stepSize <= 0) {
                stepSize = 1;
            }

            for (int j = 0, patrolGroupIndex = 0; j < groups; j++, patrolGroupIndex += stepSize) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID]
                                  .aiTribeIDs[DAT_SkirmishDefinedData::instance.MaxAIVLocationForPatrolUnits[i]
                                                  .tribeArrayOffset
                                      + j];
                if (tribeID == 0) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID]
                           .aiTribeUIDs[DAT_SkirmishDefinedData::instance.MaxAIVLocationForPatrolUnits[i]
                                            .tribeArrayOffset
                               + j]) {
                    continue;
                }

                int slot = (DAT_GameState::instance.playerDataArray[playerID].defWallPatrolRallyTimeHits
                               + patrolGroupIndex)
                    % count;
                if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0
                    && enclosed == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(tribeID, playerID);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAIVLocationSlot, this)(tribeID,
                        (AIVUnitType)DAT_SkirmishDefinedData::instance.MaxAIVLocationForPatrolUnits[i].aivUnitType,
                        slot);
                }

                if (DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker > 0
                    && enclosed == FALSE) {
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;
                } else {
                    DAT_TribesState::instance.tribes[tribeID].unitStance
                        = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;
                }
            }
        }
    }

}
}
