// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // restores the names of the AI players from the skirmish results and refreshes the AIC build intervals
    // FUNCTION: STRONGHOLDCRUSADER 0x004ECE60
    void AIVState::syncAIPlayerNamesAndBuildIntervals()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                || DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
                continue;
            }
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[playerID],
                DAT_GameSynchronyState::instance.finalResults.names[playerID]);
            int const aivID = DAT_GameState::instance.playerDataArray[playerID].aivID;
            if (aivID != 0) {
                this->aivs[aivID].aivPoorLimit_OR_AIC_buildInterval
                    = MACRO_CALL_MEMBER(AICState_Func::getAIBuildInterval, DAT_AICState::ptr)(playerID);
            }
        }
    }

}
}
