#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDBC0
    int AICState::getTargetableBuildingForPlayerID(int playerID, int param_2)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == 0)
            return 0;
        int outerPatrolGroupsCount = this->aics[aiType - 1].OuterPatrolGroupsCount;
        if (outerPatrolGroupsCount <= 0)
            return 0;
        int tracker = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;
        if (tracker <= 0)
            return 0;

        DAT_GameState::instance.playerDataArray[playerID].someCounter2++;
        if (DAT_GameState::instance.playerDataArray[playerID].someCounter2 >= tracker)
            DAT_GameState::instance.playerDataArray[playerID].someCounter2 = 0;

        int index = (tracker / outerPatrolGroupsCount * param_2
                        + DAT_GameState::instance.playerDataArray[playerID].someCounter2)
            % tracker;
        for (int i = 0; i < tracker; i++) {
            int buildingID = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings[index];
            index++;
            if (index >= tracker)
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
