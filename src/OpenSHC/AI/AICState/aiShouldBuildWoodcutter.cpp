#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB290
    BOOLEnum AICState::aiShouldBuildWoodcutter(int playerID)
    {
        if (DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 0)
            return FALSE;
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == AITA_NULL)
            return FALSE;
        int aicIndex = aiType - 1;
        if (this->aics[aicIndex].populationPerWoodcutter <= 0)
            return FALSE;

        int count = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::countBuildingsForPlayer, DAT_BuildingsState::ptr)(
            playerID, Map::Buildings::BT_WOODCUTTERSHUT, 1);
        if (count <= 0) {
            count = 1;
        } else {
            if (count >= this->aics[aicIndex].maxWoodcutters)
                return FALSE;
            if (count >= 6 && DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 90)
                return FALSE;
            if (count >= 3 && DAT_AIVState::instance.mapExtraInfo.totalWoodAvailable <= 30)
                return FALSE;
        }
        return DAT_GameState::instance.playerDataArray[playerID].currentPopulation / count
            >= this->aics[aicIndex].populationPerWoodcutter;
    }
}
}
