#include "../AICState.func.hpp"

#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D3850
    BOOLEnum AICState::determineAIPlayerHelp(int playerID, int requestedByPlayerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return FALSE;
        int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;

        if (DAT_GameState::instance.playerDataArray[playerID].isNotNervousByEnemyTroopValue != 0) {
            MACRO_CALL_MEMBER(AICState_Func::playWillNotHelp1BikFromPlayerToPlayer, this)(
                playerID, requestedByPlayerID);
            return FALSE;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
            < this->aics[aicIndex].AttForceSupportAllyThreshold) {
            MACRO_CALL_MEMBER(AICState_Func::playWillNotHelp2BikFromPlayerToPlayer, this)(
                playerID, requestedByPlayerID);
            return FALSE;
        }

        MACRO_CALL_MEMBER(AICState_Func::playWillHelpBikFromPlayerToPlayer, this)(playerID, requestedByPlayerID);
        return TRUE;
    }

}
}
