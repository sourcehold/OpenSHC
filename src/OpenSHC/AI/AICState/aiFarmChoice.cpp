#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB180
    int AICState::aiFarmChoice(PlayerID playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return 0;
        return (&this->aics[aiType - 1].farm1)[DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex];
    }
}
}
