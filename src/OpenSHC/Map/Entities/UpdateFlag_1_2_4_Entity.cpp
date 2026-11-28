#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/AI/AIRecruitUnitChoice.hpp"
#include "OpenSHC/AI/AIRecruitUnitChoiceInt.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    using AI::AIRecruitUnitChoice;
    using AI::AIRecruitUnitChoiceInt;
    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x00402900
    void Entities::UpdateFlag_1_2_4_Entity()
    {
        uint const entityID = DAT_CurrentEntityID::instance;
        int nextTracker = DAT_EntityState::instance.entityArray[entityID].someTracker;
        int const owner = DAT_EntityState::instance.entityArray[entityID].owner;
        DAT_EntityState::instance.entityArray[entityID].graphicType2
            = DAT_EntityState::instance.entityArray[entityID].graphicType2RelatedOffset;
        if (((byte)DAT_EntityState::instance.entityArray[entityID].yPosition & 0x1f)
            >= DAT_LandscapeState::instance.wind.countdown) {
            nextTracker = DAT_LandscapeState::instance.wind.value;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[owner] != 0) {
            if (DAT_GameState::instance.playerDataArray[owner].aiBuildingDestroyChoiceTracker != 0) {
                nextTracker = 3;
            } else if (DAT_GameState::instance.playerDataArray[owner].aiNervousActionsTracker != 0) {
                nextTracker = 3;
            } else {
                AIRecruitUnitChoiceInt const recruitChoice
                    = DAT_GameState::instance.playerDataArray[owner].aiRecruitUnitChoiceState;
                nextTracker = 0;
                if (recruitChoice != AI::AIRUC_DEFENSIVE) {
                    nextTracker = (recruitChoice != AI::AIRUC_RAIDING) + 1;
                }
            }
        }
        DAT_EntityState::instance.entityArray[entityID].unkOne_1 = 3;
        int frame;
        switch (DAT_EntityState::instance.entityArray[entityID].someTracker) {
        case 0:
            frame = DAT_EntityDefinedData::instance.FlagAnimationFrames1[DAT_EntityState::instance.entityArray[entityID]
                    .unknownAnimationFrameRelated];
            break;
        case 1:
            frame = DAT_EntityDefinedData::instance.FlagAnimationFrames2[DAT_EntityState::instance.entityArray[entityID]
                    .unknownAnimationFrameRelated];
            break;
        case 3:
            DAT_EntityState::instance.entityArray[entityID].unkOne_1 = 1;
            /* falls through into case 2 */
        case 2:
            frame = DAT_EntityDefinedData::instance.FlagAnimationFrames3[DAT_EntityState::instance.entityArray[entityID]
                    .unknownAnimationFrameRelated];
            break;
        default:
            return;
        }
        if (frame <= 0) {
            DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated = 0;
            DAT_EntityState::instance.entityArray[entityID].someTracker = nextTracker;
            return;
        }
        DAT_EntityState::instance.entityArray[entityID].graphicType2
            = DAT_EntityState::instance.entityArray[entityID].graphicType2 + frame - 1;
    }

}
}
