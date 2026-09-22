#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D00A0
    BOOLEnum AICState::hasNotEnoughSupplies(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].marketplace.id == 0
            && DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_WOOD]
                < DAT_BuildingsState::instance.buildingCosts[Map::Buildings::BT_MARKETPLACE].requiredWood
            && DAT_GameState::instance.playerDataArray[playerID].noLabourerBuildingCount < 1)
            return TRUE;
        if (DAT_GameState::instance.playerDataArray[playerID].granary.id == 0
            && DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_WOOD]
                < DAT_BuildingsState::instance.buildingCosts[Map::Buildings::BT_GRANARY].requiredWood
            && DAT_GameState::instance.playerDataArray[playerID].noLabourerBuildingCount <= 1)
            return TRUE;
        if (DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] <= 0
            && DAT_GameState::instance.playerDataArray[playerID].popularity <= 25
            && DAT_GameState::instance.playerDataArray[playerID].totalFood <= 0)
            return TRUE;
        return FALSE;
    }
}
}
