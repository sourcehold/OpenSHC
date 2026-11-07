#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004A15B0
        BOOLEnum PathFindingState::isEnemyTooCloseUnk(int playerID, uint x, uint y, int requiredDistance)
        {
            if (MC_MAP_XY_LIMIT_MIN_1 < x || MC_MAP_XY_LIMIT_MIN_1 < y) {
                return FALSE;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + x] == 0) {
                return FALSE;
            }
            int const requiredDistanceSquared = requiredDistance * requiredDistance;
            int* const enemyUIDs = DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList[playerID];
            int const enemies = DAT_GameState::instance.playerDataArray[playerID].enemies;
            for (int i = 0; i < enemies; ++i) {
                int const enemyID = DAT_GameState::instance.playerDataArray[playerID].enemyIDArray[i];
                if (DAT_UnitsState::instance.units[enemyID].dying != 0
                    || DAT_UnitsState::instance.units[enemyID].uid != enemyUIDs[i]) {
                    continue;
                }
                int const dx = x - DAT_UnitsState::instance.units[enemyID].x;
                int const dy = y - DAT_UnitsState::instance.units[enemyID].y;
                if (dy * dy + dx * dx < requiredDistanceSquared
                    && DAT_UnitsState::instance.units[enemyID].unknownTestAgainst0_2 == 0
                    && DAT_UnitsState::instance.units[enemyID].moveRelatedFlag != 1
                    && DAT_UnitsState::instance.units[enemyID].isStalked == 0
                    && DAT_UnitsState::instance.units[enemyID].owner != 0) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
