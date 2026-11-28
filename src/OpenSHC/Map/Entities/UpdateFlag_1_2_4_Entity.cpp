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
        AIRecruitUnitChoiceInt AVar1;
        uint uVar2;
        int iVar3;
        short sVar4;
        short _owner;
        uVar2 = DAT_CurrentEntityID::instance;
        sVar4 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker;
        _owner = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        if (DAT_LandscapeState::instance.wind.countdown
            <= (int)((byte)DAT_EntityState::instance.entityArray[uVar2].yPosition & 0x1f)) {
            sVar4 = (short)DAT_LandscapeState::instance.wind.value;
        }
        if (((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_owner] == -1))
            && (DAT_GameSynchronyState::instance.currentAIArray[_owner] != 0)) {
            if (DAT_GameState::instance.playerDataArray[_owner].aiBuildingDestroyChoiceTracker == 0) {
                if (DAT_GameState::instance.playerDataArray[_owner].aiNervousActionsTracker == 0) {
                    AVar1 = DAT_GameState::instance.playerDataArray[_owner].aiRecruitUnitChoiceState;
                    sVar4 = 0;
                    if (AVar1 != AI::AIRUC_DEFENSIVE) {
                        sVar4 = (AVar1 != AI::AIRUC_RAIDING) + 1;
                    }
                } else {
                    sVar4 = 3;
                }
            } else {
                sVar4 = 3;
            }
        }
        DAT_EntityState::instance.entityArray[uVar2].unkOne_1 = 3;
        switch (DAT_EntityState::instance.entityArray[uVar2].someTracker) {
        case 0:
            iVar3
                = DAT_EntityDefinedData::instance
                      .FlagAnimationFrames1[DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
            break;
        case 1:
            iVar3
                = DAT_EntityDefinedData::instance
                      .FlagAnimationFrames2[DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
            break;
        case 3:
            DAT_EntityState::instance.entityArray[uVar2].unkOne_1 = 1;
            /* falls through into case 2 */
        case 2:
            iVar3
                = DAT_EntityDefinedData::instance
                      .FlagAnimationFrames3[DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated];
            break;
        default:
            return;
        }
        if (iVar3 < 1) {
            DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated = 0;
            DAT_EntityState::instance.entityArray[uVar2].someTracker = sVar4;
        }
        DAT_EntityState::instance.entityArray[uVar2].graphicType2
            = DAT_EntityState::instance.entityArray[uVar2].graphicType2 + iVar3 + -1;
    }

}
}
