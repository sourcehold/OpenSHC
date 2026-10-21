#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419EB0
        int BuildingsState::aiFindBuildingToAttack(int playerID, int x, int y, int radius)
        {
            int closestDistance = 1000000;
            int closestBuildingID = 0;
            int const radiusSquared = radius * radius;
            for (int i = 0; i < DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[playerID]; ++i) {
                int const buildingID = DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[playerID][i];
                if (this->buildings[buildingID].uid
                        != DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[playerID][i]
                    || this->buildings[buildingID].fireDuration != 0) {
                    continue;
                }
                int const flammability = MACRO_CALL_MEMBER(
                    BuildingsState_Func::getBuildingFlammabilityFactor, DAT_BuildingsState::ptr)(buildingID);
                if (flammability == 0 || flammability == 4) {
                    continue;
                }
                int const dx = x - this->buildings[buildingID].x;
                int const dy = y - this->buildings[buildingID].y;
                int const distance = dy * dy + dx * dx;
                if (distance <= radiusSquared && distance < closestDistance) {
                    closestDistance = distance;
                    closestBuildingID = buildingID;
                }
            }
            return closestBuildingID;
        }

    }
}
}
