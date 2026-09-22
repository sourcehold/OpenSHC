#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDCF0
    BOOLEnum AICState::aiShouldAttackOrWaitForTeamCoordination(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == OpenSHC::AI::AIT_NULL)
            return FALSE;
        int aicIndex = aiType - 1;
        if (DAT_GameState::instance.playerDataArray[playerID].requestStateUnk == 1)
            return TRUE;

        if (DAT_GameState::instance.playerDataArray[DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID]
                .totalTroopValue
            <= 100)
            DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength = 0;

        if (DAT_GameState::instance.playerDataArray[playerID].totalAttackTroops
                - DAT_GameState::instance.playerDataArray[playerID].totalAttackingEngineerTroops
            < this->aics[aicIndex].AttForceBase
                + DAT_GameState::instance.playerDataArray[playerID].currentWaveRandomAttackingStrength)
            return FALSE;
        if (DAT_GameState::instance.playerDataArray[playerID].aiAttackCoordinationLevel == 0)
            return TRUE;

        int readyTeamMembers = 0;
        int unreadyTeamMembers = 0;
        for (int otherPlayerID = 1; otherPlayerID < 9; otherPlayerID++) {
            if (otherPlayerID == playerID)
                continue;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                    otherPlayerID)
                == 0)
                continue;
            if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(
                    otherPlayerID)
                == FALSE)
                continue;
            if (DAT_GameState::instance.mapAndTime.playerTeams[otherPlayerID]
                != DAT_GameState::instance.mapAndTime.playerTeams[playerID])
                continue;

            if (DAT_GameState::instance.playerDataArray[otherPlayerID].aiPlayerState != 0)
                return TRUE;
            if (DAT_GameState::instance.playerDataArray[otherPlayerID].totalAttackTroops
                    - DAT_GameState::instance.playerDataArray[otherPlayerID].totalAttackingEngineerTroops
                >= this->aics[DAT_GameState::instance.playerDataArray[otherPlayerID].aiType - 1].AttForceBase
                    + DAT_GameState::instance.playerDataArray[otherPlayerID].currentWaveRandomAttackingStrength)
                readyTeamMembers++;
            else
                unreadyTeamMembers++;
        }

        if (readyTeamMembers >= DAT_GameState::instance.playerDataArray[playerID].aiAttackCoordinationLevel)
            return TRUE;
        if (unreadyTeamMembers == 0)
            return TRUE;

        DAT_GameState::instance.playerDataArray[playerID].aiCoordinatedAttackPatience++;
        if (DAT_GameState::instance.playerDataArray[playerID].aiCoordinatedAttackPatience > 48
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_CAMPAIGN_MISSION)
            return TRUE;
        return FALSE;
    }

}
}
