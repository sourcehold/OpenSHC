#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004cb120
    int AICState::getAIBuildInterval(int playerID)

    {
        int _aiType;

        _aiType = DAT_GameState::ptr->playerDataArray[playerID].aiType;
        if (_aiType == 0) {
            return _aiType;
        }

        return this->DAT_AICArray[(_aiType - 1)].buildInterval;
    }
}
}
