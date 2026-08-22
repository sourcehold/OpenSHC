#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CBFA0
    void AICState::sellGoods(int playerID, ResourceType resourceType, int amount)
    {
        int _yield = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
            playerID, resourceType, amount);
        int* _pFinalGold = DAT_GameSynchronyState::instance.SEC_FinalResults.finalGold + playerID;
        *_pFinalGold = *_pFinalGold + _yield;
        int* _pGold = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0xf;
        *_pGold = *_pGold + _yield;
        int* _pGoldSell = &DAT_GameState::instance.playerDataArray[playerID].marketGold;
        *_pGoldSell = *_pGoldSell + _yield;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
            playerID, resourceType, amount, 0);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::displayPlayerTradeVisualEffect, DAT_GameState::ptr)(
            playerID, 1, -amount, resourceType);
    }
}
}
