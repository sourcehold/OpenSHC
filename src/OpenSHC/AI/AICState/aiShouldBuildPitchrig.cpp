#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB540
    uint AICState::aiShouldBuildPitchrig(PlayerID param_1)
    {
        int const aiType = DAT_GameState::instance.playerDataArray[param_1].aiType;
        if (aiType == AITA_NULL) {
            return 0;
        }
        AICSpecification const* spec = &this->aics[aiType - 1];
        if ((int)spec->populationPerPitchrig <= 0) {
            return 0;
        }
        int iVar3 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
            DAT_BuildingsState::ptr)(param_1, Map::Buildings::BT_PITCHRIG, 1);
        if (iVar3 < 1) {
            iVar3 = 1;
        } else {
            if (iVar3 >= (int)spec->maxPitchrigs) {
                return 0;
            }
        }
        return DAT_GameState::instance.playerDataArray[param_1].currentPopulation / iVar3
            >= (int)spec->populationPerPitchrig;
    }
}
}
