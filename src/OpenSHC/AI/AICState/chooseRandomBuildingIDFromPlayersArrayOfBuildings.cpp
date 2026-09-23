#include "../AICState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDB20
    int AICState::chooseRandomBuildingIDFromPlayersArrayOfBuildings(int playerID)
    {
        int chosenBuildingID = 0;
        int chosenPriority = 46;
        int buildingCount = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;
        int rng = SEC_RNG::instance.currentNumber2 & 7;
        for (int i = 0; i < buildingCount; i++) {
            int buildingID = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings[i];
            if (buildingID == 0)
                continue;

            int buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
            for (int j = 0; j < chosenPriority; j++) {
                bool isMatch;
                if (rng <= 1)
                    isMatch = buildingType == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet3[j];
                else if (rng <= 3)
                    isMatch = buildingType == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet2[j];
                else
                    isMatch = buildingType == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1[j];

                if (isMatch) {
                    chosenBuildingID = buildingID;
                    chosenPriority = j;
                }
            }
        }
        return chosenBuildingID;
    }

}
}
