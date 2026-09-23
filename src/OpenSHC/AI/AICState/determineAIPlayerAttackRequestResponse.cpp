#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D38C0
    BOOLEnum AICState::determineAIPlayerAttackRequestResponse(int playerID, undefined4 param_2, int requestedByPlayerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return FALSE;
        int aicIndex = aiType - 1;

        if (DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue != 0) {
            MACRO_CALL_MEMBER(AICState_Func::playWillNotAttack1BikFromPlayerToPlayer, this)(
                playerID, requestedByPlayerID);
            return FALSE;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
                - DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops
            < this->aics[aicIndex].AttForceSupportAllyThreshold) {
            MACRO_CALL_MEMBER(AICState_Func::playWillNotAttack2BikFromPlayerToPlayer, this)(
                playerID, requestedByPlayerID);
            return FALSE;
        }

        MACRO_CALL_MEMBER(AICState_Func::playWillAttackBikFromPlayerToPlayer, this)(playerID, requestedByPlayerID);
        return TRUE;
    }

}
}
