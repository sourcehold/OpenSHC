#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDBC0
    int AICState::getTargetableBuildingForPlayerID(int playerID, int param_2)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == 0)
            return 0;
        int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
        if (this->aics[aicIndex].OuterPatrolGroupsCount <= 0)
            return 0;
        if (DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker <= 0)
            return 0;

        int step = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker
            / this->aics[aicIndex].OuterPatrolGroupsCount;
        DAT_GameState::instance.playerDataArray[playerID].someCounter2++;
        if (DAT_GameState::instance.playerDataArray[playerID].someCounter2
            >= DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker)
            DAT_GameState::instance.playerDataArray[playerID].someCounter2 = 0;
        int index = (step * param_2 + DAT_GameState::instance.playerDataArray[playerID].someCounter2)
            % DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;
        for (int i = 0; i < DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker; i++) {
            int buildingID = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings[index];
            index++;
            if (index >= DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker)
                index = 0;
            if (buildingID == 0)
                continue;

            for (int j = 0; j < 8; j++) {
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1[j])
                    return buildingID;
            }
        }
        return 0;
    }

}
}
