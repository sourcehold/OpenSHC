#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB330
    uint AICState::aiShouldBuildQuarry(PlayerID playerID)
    {
        int const aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL) {
            return 0;
        }
        AICSpecification const* spec = &this->DAT_AICArray[aiType - 1];
        if ((int)spec->populationPerQuarry <= 0) {
            return 0;
        }
        int _quarryCount = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
            DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_QUARRY, 1);
        if (_quarryCount < 1) {
            _quarryCount = 1;
        } else if (_quarryCount >= (int)spec->maxQuarries) {
            return 0;
        }
        return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / _quarryCount
            >= (int)spec->populationPerQuarry;
    }
}
}
