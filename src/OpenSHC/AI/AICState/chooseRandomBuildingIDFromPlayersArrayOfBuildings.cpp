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
        int const rng = SEC_RNG::instance.currentNumber2 & 7;
        int chosenBuildingID = 0;
        int chosenPriority = countof(DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1);
        for (int i = 0; i < DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker; ++i) {
            int const buildingID = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings[i];
            if (buildingID == 0)
                continue;

            // The stores stay in each arm: one shared copy behind the three tests loses the match.
            for (int j = 0; j < chosenPriority; ++j) {
                if (rng <= 1) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet3[j]) {
                        chosenPriority = j;
                        chosenBuildingID = buildingID;
                    }
                } else if (rng <= 3) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet2[j]) {
                        chosenPriority = j;
                        chosenBuildingID = buildingID;
                    }
                } else {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                        == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1[j]) {
                        chosenPriority = j;
                        chosenBuildingID = buildingID;
                    }
                }
            }
        }
        return chosenBuildingID;
    }

}
}
