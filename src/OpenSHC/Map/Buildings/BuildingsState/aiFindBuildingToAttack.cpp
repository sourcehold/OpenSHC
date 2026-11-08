#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419EB0
        int BuildingsState::aiFindBuildingToAttack(int param_1, int param_2, int param_3, int param_4)
        {
            // Matching note: The original keeps the building pointer in edx across getBuildingFlammabilityFactor,
            // which needs /GL (the callee is already in cmake/compiler-flags-gl.txt, this file is not); without it
            // the pointer takes esi and the ID difference spills.
            // Finds the closest flammable enemy building of player param_1 within radius param_4 around (param_2,
            // param_3)
            int closest = 0;
            int closestDistance = 1000000;
            int const* const enemyIDs = DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[param_1];
            int const* const enemyUIDs = DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[param_1];
            int const radiusSquared = param_4 * param_4;
            int const count = DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[param_1];
            for (int i = 0; i < count; ++i) {
                int buildingID = enemyIDs[i];
                if (this->buildings[buildingID].uid != enemyUIDs[i] || this->buildings[buildingID].fireDuration != 0) {
                    continue;
                }
                int flammability
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor,
                        DAT_BuildingsState::ptr)(buildingID);
                if (flammability == 0 || flammability == 4) {
                    continue;
                }
                int dx = param_2 - (short)this->buildings[buildingID].x;
                int dy = param_3 - (short)this->buildings[buildingID].y;
                int distance = dy * dy + dx * dx;
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
