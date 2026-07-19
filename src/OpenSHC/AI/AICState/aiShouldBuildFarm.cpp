#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB220
    uint AICState::aiShouldBuildFarm(PlayerID playerID)
    {
        int const aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return 0;
        }
        int _farmCount
            = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countFarms, DAT_BuildingsState::ptr)(playerID, 1);
        if (_farmCount < 1) {
            return 1;
        }
        AICSpecification const* spec = &this->DAT_AICArray[aiType - 1];
        if (_farmCount >= (int)spec->maxFarms) {
            return 0;
        }
        return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / _farmCount
            >= (int)spec->populationPerFarm;
    }
}
}
