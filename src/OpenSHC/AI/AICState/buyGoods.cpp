#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC000
    BOOLEnum AICState::buyGoods(int playerID, ResourceType resourceType, int amount)
    {
        int _cost = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getBuyPrice, DAT_GameState::ptr)(
            playerID, resourceType, amount);
        BOOLEnum _gain = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceGain,
            DAT_BuildingsState::ptr)(playerID, resourceType, amount);
        if (_gain != FALSE) {
            int* piVar1 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0xf;
            *piVar1 = *piVar1 - _cost;
            piVar1 = &DAT_GameState::instance.playerDataArray[playerID].marketGold;
            *piVar1 = *piVar1 - _cost;
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::displayPlayerTradeVisualEffect, DAT_GameState::ptr)(
                playerID, 0, amount, resourceType);
            return TRUE;
        }
        return FALSE;
    }
}
}
