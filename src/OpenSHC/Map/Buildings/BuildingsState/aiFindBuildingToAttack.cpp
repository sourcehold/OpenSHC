#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419EB0
        int BuildingsState::aiFindBuildingToAttack(int param_1, int param_2, int param_3, int param_4)
        {
            // Finds the closest flammable enemy building of player param_1 within radius param_4 around (param_2,
            // param_3).
            // Matching note: the original keeps the building pointer in edx across getBuildingFlammabilityFactor,
            // which needs /GL (cmake/compiler-flags-gl.txt) for both this file and the callee.
            int closest = 0;
            int closestDistance = 1000000;
            // Matching note: indexing the two arrays directly instead of through these pointers drops to 0.62
            int const* const enemyIDs = DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[param_1];
            int const* const enemyUIDs = DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[param_1];
            int const radiusSquared = param_4 * param_4;
            int const count = DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[param_1];
            for (int i = 0; i < count; ++i) {
                int const buildingID = enemyIDs[i];
                if (this->buildings[buildingID].uid != enemyUIDs[i] || this->buildings[buildingID].fireDuration != 0) {
                    continue;
                }
                int const flammability
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor,
                        DAT_BuildingsState::ptr)(buildingID);
                if (flammability == 0 || flammability == 4) {
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
