#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419FA0
        int BuildingsState::findClosestEnemyBuildingWithinRadius(int param_1, int param_2, int param_3, int param_4)
        {
            int closestBuildingID = 0;
            int closestDistance = 1000000;
            for (int i = 0; i < DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[param_1]; ++i) {
                int const buildingID = DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[param_1][i];
                if (this->buildings[buildingID].uid
                    == DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[param_1][i]) {
                    int const dx = param_2 - this->buildings[buildingID].x;
                    int const dy = param_3 - this->buildings[buildingID].y;
                    int const distance = dy * dy + dx * dx;
                    if (distance <= param_4 * param_4 && distance < closestDistance) {
                        closestDistance = distance;
                        closestBuildingID = buildingID;
                    }
                }
            }
            return closestBuildingID;
        }

    }
}
}
