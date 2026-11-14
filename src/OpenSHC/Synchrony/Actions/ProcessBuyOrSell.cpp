#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00465E60
    void Actions::ProcessBuyOrSell(int playerID, int buyOrSell, ResourceType resourceType)
    {
        if (buyOrSell == 0) {
            int const price = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getBatchBuyPrice, DAT_GameState::ptr)(
                playerID, resourceType);
            if (price <= DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD]
                && MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceGain, DAT_BuildingsState::ptr)(
                    playerID, resourceType, 5)) {
                DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] -= price;
                DAT_GameState::instance.playerDataArray[playerID].marketGold -= price;
            }
        } else if (buyOrSell == 1) {
            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] >= 0) {
                int const amount = MACRO_CALL_MEMBER(
                    Game::GameStateStructures_Func::getSellResourceAmount, DAT_GameState::ptr)(playerID, resourceType);
                int const price = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalesPrice, DAT_GameState::ptr)(
                    playerID, resourceType);
                DAT_GameSynchronyState::instance.finalResults.finalGold[playerID] += price;
                DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] += price;
                DAT_GameState::instance.playerDataArray[playerID].marketGold += price;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
                    playerID, resourceType, amount, 0);
            }
        }
    }

}
}
