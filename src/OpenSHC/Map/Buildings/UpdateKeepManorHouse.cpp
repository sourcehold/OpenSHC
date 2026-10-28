#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004178E0
    void Buildings::UpdateKeepManorHouse()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentHealth
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].maxHealth;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someX
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x + 3;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someY
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y + 9;
        if ((DAT_GameCore::instance.mapTimeInTicks & 3) != 0) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR
            || DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
            return;
        }
        // The starting gold is paid out into the treasury in steps.
        int const startingGold
            = DAT_GameState::instance.playerDataArray[owner].startResources[Game::Resources::RT_GOLD];
        if (startingGold <= 0) {
            return;
        }
        int amount = 1;
        if (startingGold > 1000) {
            amount = 100;
        } else if (startingGold > 100) {
            amount = 10;
        }
        int const remainingGold = startingGold - amount;
        DAT_GameState::instance.playerDataArray[owner].currentResources[Game::Resources::RT_GOLD] += amount;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resourceRelatedCountDown = 100;
        DAT_GameState::instance.playerDataArray[owner].startResources[Game::Resources::RT_GOLD] = remainingGold;
        DAT_GameState::instance.playerDataArray[owner].beforeLastMonthsGold
            = DAT_GameState::instance.playerDataArray[owner].currentResources[Game::Resources::RT_GOLD];
        DAT_GameState::instance.playerDataArray[owner].lastMonthsGold
            = DAT_GameState::instance.playerDataArray[owner].currentResources[Game::Resources::RT_GOLD];
        DAT_GameCore::instance.countdown = 1;
    }

}
}
