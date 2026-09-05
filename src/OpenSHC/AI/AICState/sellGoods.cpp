#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CBFA0
    void AICState::sellGoods(int playerID, ResourceType resourceType, int amount)
    {
        int const reward = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
            playerID, resourceType, amount);
        DAT_GameSynchronyState::ptr->finalResults.finalGold[playerID] += reward;
        DAT_GameState::ptr->playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD] += reward;
        DAT_GameState::ptr->playerDataArray[playerID].marketGold += reward;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
            playerID, resourceType, amount, 0);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::displayPlayerTradeVisualEffect, DAT_GameState::ptr)(
            playerID, 1, -amount, resourceType);
    }

}
}
