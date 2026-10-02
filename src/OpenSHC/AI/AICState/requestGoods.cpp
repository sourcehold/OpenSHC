#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1F00
    void AICState::requestGoods(int playerID, ResourceType resourceType, int amount)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].aiRequestDelay != 0) {
            return;
        }
        // Never request raw farm goods or ale
        if (resourceType == OpenSHC::Game::Resources::RT_WHEAT || resourceType == OpenSHC::Game::Resources::RT_HOPS
            || resourceType == OpenSHC::Game::Resources::RT_ALE) {
            return;
        }
        // Only request food when almost out of it
        if ((resourceType == OpenSHC::Game::Resources::RT_BREAD || resourceType == OpenSHC::Game::Resources::RT_CHEESE
                || resourceType == OpenSHC::Game::Resources::RT_MEAT
                || resourceType == OpenSHC::Game::Resources::RT_APPLE)
            && DAT_GameState::instance.playerDataArray[playerID].totalFood >= 5) {
            return;
        }
        // fixme: NOTE: the original performs the exact same food check a second time, it cannot be removed
        if ((resourceType == OpenSHC::Game::Resources::RT_BREAD || resourceType == OpenSHC::Game::Resources::RT_CHEESE
                || resourceType == OpenSHC::Game::Resources::RT_MEAT
                || resourceType == OpenSHC::Game::Resources::RT_APPLE)
            && DAT_GameState::instance.playerDataArray[playerID].totalFood >= 5) {
            return;
        }

        // Ask every human teammate that has no pending request from this player
        for (int i = 1; i < 9; i++) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] == -1) {
                continue;
            }
            if (DAT_GameState::instance.mapAndTime.playerTeams[i]
                != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                continue;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(i)
                == 0) {
                continue;
            }
            if (DAT_GameState::instance.playerDataArray[i].requestedGoodsArray1Unk[playerID] != 0) {
                continue;
            }

            DAT_GameState::instance.playerDataArray[i].requestedGoodsArray1Unk[playerID] = resourceType;
            DAT_GameState::instance.playerDataArray[i].requestedGoodsArray2Unk[playerID] = amount;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playGoodsRequestBikFromPlayerToPlayer, this)(playerID, i);
        }
    }

}
}
