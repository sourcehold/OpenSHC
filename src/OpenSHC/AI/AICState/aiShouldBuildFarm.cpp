#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB220
    BOOLEnum AICState::aiShouldBuildFarm(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return FALSE;
        int aicIndex = aiType - 1;

        int farmCount
            = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countFarms, DAT_BuildingsState::ptr)(playerID, 1);
        if (farmCount <= 0)
            return TRUE;
        if (farmCount >= this->aics[aicIndex].maxFarms)
            return FALSE;
        return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / farmCount
            >= this->aics[aicIndex].populationPerFarm;
    }
}
}
