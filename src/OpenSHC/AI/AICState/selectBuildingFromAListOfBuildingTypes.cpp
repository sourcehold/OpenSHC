#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDAB0
    int AICState::selectBuildingFromAListOfBuildingTypes(int playerID)
    {
        // Pick the targetable building whose type comes first in BuildingTargetPrioritySet1
        int selectedBuildingID = 0;
        int bestPriority = 46;
        for (int i = 0; i < DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker; i++) {
            int buildingID = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings[i];
            if (buildingID == 0) {
                continue;
            }
            for (int j = 0; j < bestPriority; j++) {
                if ((short)DAT_BuildingsState::instance.buildings[buildingID].buildingType
                    == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1[j]) {
                    // Found a better match; lowering the bound also ends this loop
                    bestPriority = j;
                    selectedBuildingID = buildingID;
                }
            }
        }

        return selectedBuildingID;
    }

}
}
