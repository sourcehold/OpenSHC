#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C1A0
        BOOLEnum BuildingsState::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters(int playerID, int param_2)
        {
            if (DAT_GameCore::instance.gameMode_2 == 6) {
                return FALSE;
            }
            if (param_2 != 3) {
                return FALSE;
            }
            if (MACRO_CALL_MEMBER(BuildingsState_Func::findFirstBuildingOfType, this)(playerID, BT_WOODCUTTERSHUT)
                != 0) {
                return FALSE;
            }
            return DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_WOOD]
                < DAT_BuildingsState::instance.buildingCosts[BT_WOODCUTTERSHUT].requiredWood;
        }

    }
}
}
