#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB120
    int AICState::getAIBuildInterval(int playerID)

    {
        int const aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return 0;
        }

        return this->DAT_AICArray[(aiType - 1)].buildInterval;
    }
}
}
