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
        for (int i = 0; i < DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker; i++) {
            int rng = SEC_RNG::instance.currentNumber2 & 7;
            int buildingID = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings[i];
            if (buildingID == 0)
                continue;

            for (int j = 0; j < chosenPriority; j++) {
                if (rng <= 1) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        != DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet3[j])
                        continue;
                } else if (rng <= 3) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        != DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet2[j])
                        continue;
                } else {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        != DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1[j])
                        continue;
                }

                chosenBuildingID = buildingID;
                chosenPriority = j;
            }
        }
        return chosenBuildingID;
    }

}
}
