#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D00A0
    BOOLEnum AICState::hasNotEnoughSupplies(int playerID)
    {
        BOOLEnum BVar1 = TRUE;
        if (DAT_GameState::instance.playerDataArray[playerID].marketplace.id == 0
            && DAT_GameState::instance.playerDataArray[playerID].currentResources[2]
                < DAT_BuildingsState::instance.buildingCosts[0x1a].requiredWood
            && DAT_GameState::instance.playerDataArray[playerID].noLabourerBuildingCount < 1) {
            return BVar1;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].granary.id == 0
            && DAT_GameState::instance.playerDataArray[playerID].currentResources[2]
                < DAT_BuildingsState::instance.buildingCosts[0x13].requiredWood
            && DAT_GameState::instance.playerDataArray[playerID].noLabourerBuildingCount <= 1) {
            return BVar1;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] <= 0
            && DAT_GameState::instance.playerDataArray[playerID].popularity <= 25
            && DAT_GameState::instance.playerDataArray[playerID].totalFood <= 0) {
            return BVar1;
        }
        return FALSE;
    }
}
}
