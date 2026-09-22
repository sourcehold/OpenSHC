#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0580
    BOOLEnum AICState::aiOfTypeInCurrentGame(int aicIndex)
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            if (DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0)
                continue;
            if (DAT_GameState::instance.playerDataArray[playerID].lordKilledByPlayerID != 0)
                continue;
            if (DAT_GameState::instance.playerDataArray[playerID].aiType - 1 != aicIndex)
                continue;
            return TRUE;
        }
        return FALSE;
    }

}
}
