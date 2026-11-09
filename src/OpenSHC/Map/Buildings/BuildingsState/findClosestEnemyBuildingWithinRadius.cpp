#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419FA0
        int BuildingsState::findClosestEnemyBuildingWithinRadius(int param_1, int param_2, int param_3, int param_4)
        {
            // Finds the closest enemy building of player param_1 within radius param_4 around (param_2, param_3)
            int closest = 0;
            int closestDistance = 1000000;
            // The original computes both row bases up front and walks the UIDs, reading the IDs at their difference;
            // indexing the arrays directly instead of through these row pointers measured 1.00 -> 0.56
            int const* const enemyIDs = DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[param_1];
            int const* const enemyUIDs = DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[param_1];
            int const radiusSquared = param_4 * param_4;
            int const count = DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[param_1];
            for (int i = 0; i < count; ++i) {
                int const buildingID = enemyIDs[i];
                if (this->buildings[buildingID].uid != enemyUIDs[i]) {
                    continue;
                }
                int const dx = param_2 - this->buildings[buildingID].x;
                int const dy = param_3 - this->buildings[buildingID].y;
                int const distance = dy * dy + dx * dx;
                if (distance <= radiusSquared && distance < closestDistance) {
                    closestDistance = distance;
                    closest = buildingID;
                }
            }
            return closest;
        }

    }
}
}
