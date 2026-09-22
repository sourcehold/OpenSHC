#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB1B0
    int AICState::setNextFarmTypeToBuild(PlayerID playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return 0;
        int aicIndex = aiType - 1;

        DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex++;
        if (DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex >= 8)
            DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex = 0;
        if ((&this->aics[aicIndex].farm1)[DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex] == 0)
            DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex = 0;
        return (&this->aics[aicIndex].farm1)[DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex];
    }
}
}
