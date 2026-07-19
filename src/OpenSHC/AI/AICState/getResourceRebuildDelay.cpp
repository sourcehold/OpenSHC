#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB150
    int AICState::getResourceRebuildDelay(int playerID)

    {
        int const aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return 0;
        }

        return this->DAT_AICArray[(aiType - 1)].resourceRebuildDelay;
    }
}
}
