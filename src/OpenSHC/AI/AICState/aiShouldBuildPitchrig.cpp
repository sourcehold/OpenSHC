#include "../AICState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB540
    BOOLEnum AICState::aiShouldBuildPitchrig(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return FALSE;
        int aicIndex = aiType - 1;
        if (this->aics[aicIndex].populationPerPitchrig <= 0)
            return FALSE;

        int count = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
            DAT_BuildingsState::ptr)(playerID, Map::Buildings::BT_PITCHRIG, TRUE);
        if (count <= 0)
            count = 1;
        else if (count >= this->aics[aicIndex].maxPitchrigs)
            return FALSE;
        return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / count
            >= this->aics[aicIndex].populationPerPitchrig;
    }
}
}
