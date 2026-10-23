#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419EB0
        int BuildingsState::aiFindBuildingToAttack(int param_1, int param_2, int param_3, int param_4)
        {
            // Finds the closest flammable enemy building of player param_1 within radius param_4 around (param_2,
            // param_3)
            int closestDistance = 1000000;
            int closest = 0;
            for (int i = 0; i < DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[param_1]; ++i) {
                int buildingID = DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[param_1][i];
                if (this->buildings[buildingID].uid
                        != DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[param_1][i]
                    || this->buildings[buildingID].fireDuration != 0) {
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
                if (distance <= param_4 * param_4 && distance < closestDistance) {
                    closestDistance = distance;
                    closest = buildingID;
                }
            }
            return closest;
        }

    }
}
}
