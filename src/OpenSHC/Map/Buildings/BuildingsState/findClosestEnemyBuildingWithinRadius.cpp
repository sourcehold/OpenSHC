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
            int const* ids = DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[param_1];
            int const* uids = DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[param_1];
            int const radiusSq = param_4 * param_4;
            for (int i = 0; i < DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[param_1]; ++i) {
                int const buildingID = ids[i];
                if (this->buildings[buildingID].uid == uids[i]) {
                    int const dx = param_2 - this->buildings[buildingID].x;
                    int const dy = param_3 - this->buildings[buildingID].y;
                    int const distance = dy * dy + dx * dx;
                    if (distance <= radiusSq && distance < closestDistance) {
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
