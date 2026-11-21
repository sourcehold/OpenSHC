#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419FA0
        int BuildingsState::findClosestEnemyBuildingWithinRadius(int playerID, int x, int y, int radius)
        {
            // Finds the closest enemy building of player playerID within radius around (x, y)
            int closest = 0;
            int closestDistance = 1000000;
            int const* const enemyIDs = DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[playerID];
            int const* const enemyUIDs = DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[playerID];
            int const radiusSquared = radius * radius;
            int const count = DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[playerID];
            for (int i = 0; i < count; ++i) {
                int const buildingID = enemyIDs[i];
                if (this->buildings[buildingID].uid != enemyUIDs[i]) {
                    continue;
                }
                int const dx = x - this->buildings[buildingID].x;
                int const dy = y - this->buildings[buildingID].y;
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
