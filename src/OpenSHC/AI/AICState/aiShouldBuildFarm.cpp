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
        unsigned int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return (BOOLEnum)aiType;
        }
        aiType -= 1;
        int const _farmCount
            = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countFarms, DAT_BuildingsState::ptr)(playerID, 1);
        if (_farmCount <= 0) {
            return TRUE;
        }
        if (_farmCount < (int)this->aics[aiType].maxFarms) {
            return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / _farmCount
                >= (int)this->aics[aiType].populationPerFarm;
        }
        return FALSE;
    }
}
}
