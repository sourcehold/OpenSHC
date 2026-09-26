#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFF60
    BOOLEnum AICState::yieldCowThrow(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType != AITA_NULL) {
            int aicIndex = aiType - 1;
            if (DAT_GameState::instance.mapAndTime.skirmishNoCowThrowing == 0
                && this->aics[aicIndex].CowThrowInterval != 0
                && DAT_GameState::instance.playerDataArray[playerID].counter > 0) {
                DAT_GameState::instance.playerDataArray[playerID].aiCowThrowCounter++;
                if (DAT_GameState::instance.playerDataArray[playerID].aiCowThrowCounter
                    > this->aics[aicIndex].CowThrowInterval) {
                    DAT_GameState::instance.playerDataArray[playerID].aiCowThrowCounter = 0;
                    return TRUE;
                }
            }
        }
        return FALSE;
    }
}
}
