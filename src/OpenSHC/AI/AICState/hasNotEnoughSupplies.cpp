#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D00A0
    BOOLEnum AICState::hasNotEnoughSupplies(int playerID)
    {
        BOOLEnum BVar1 = TRUE;
        if (((((DAT_GameState::instance.playerDataArray[playerID].marketplace.id != 0) ||
            (DAT_BuildingsState::instance.buildingCosts[0x1a].requiredWood <= DAT_GameState::instance.playerDataArray[playerID].currentResources[2])) ||
            (0 < DAT_GameState::instance.playerDataArray[playerID].noLabourerBuildingCount)) &&
            (((DAT_GameState::instance.playerDataArray[playerID].granary.id != 0 ||
            (DAT_BuildingsState::instance.buildingCosts[0x13].requiredWood <= DAT_GameState::instance.playerDataArray[playerID].currentResources[2])) ||
            (1 < DAT_GameState::instance.playerDataArray[playerID].noLabourerBuildingCount)))) &&
            (((0 < DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] ||
            (25 < DAT_GameState::instance.playerDataArray[playerID].popularity)) ||
            (0 < DAT_GameState::instance.playerDataArray[playerID].totalFood)))) {
            BVar1 = FALSE;
        }
        return BVar1;
    }
}
}
