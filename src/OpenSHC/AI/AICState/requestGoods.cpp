#include "OpenSHC/AI/AICState.func.hpp"
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
    void AICState ::requestGoods(int playerID, ResourceType resourceType, int amount)

    {

        if ((((((DAT_GameState::instance.playerDataArray[playerID].aiType != OpenSHC::AI::AIT_NULL)
                   && (DAT_GameState::instance.playerDataArray[playerID].aiRequestDelay == 0))
                  && (resourceType != OpenSHC::Game::Resources::RT_WHEAT))
                 && ((resourceType != OpenSHC::Game::Resources::RT_HOPS
                     && (resourceType != OpenSHC::Game::Resources::RT_ALE))))
                && ((((resourceType != OpenSHC::Game::Resources::RT_BREAD
                          && ((resourceType != OpenSHC::Game::Resources::RT_CHEESE
                              && (resourceType != OpenSHC::Game::Resources::RT_MEAT))))
                         && (resourceType != OpenSHC::Game::Resources::RT_APPLE))
                    || (DAT_GameState::instance.playerDataArray[playerID].totalFood < 5))))
            && (((((resourceType != OpenSHC::Game::Resources::RT_BREAD
                       && (resourceType != OpenSHC::Game::Resources::RT_CHEESE))
                      && (resourceType != OpenSHC::Game::Resources::RT_MEAT))
                     && (resourceType != OpenSHC::Game::Resources::RT_APPLE))
                || (DAT_GameState::instance.playerDataArray[playerID].totalFood < 5)))) {

            int iVar1;
            int _playerID = 1;

            short* psVar2 = DAT_GameState::instance.playerDataArray[1].requestedGoodsArray1Unk + playerID;

            do {

                if (((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1)
                        && (DAT_GameState::instance.mapAndTime.playerTeams[_playerID]
                            == DAT_GameState::instance.mapAndTime.playerTeams[playerID]))
                    && ((iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer,
                             DAT_UnitsState::ptr)(_playerID),
                        iVar1 != 0 && (*psVar2 == 0)))) {

                    *psVar2 = (short)resourceType;

                    psVar2[10] = (short)amount;

                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playGoodsRequestBikFromPlayerToPlayer, this)(
                        playerID, _playerID);
                }

                _playerID = _playerID + 1;

                psVar2 = psVar2 + 0x1cfa;

            } while (_playerID < 9);
        }

        return;
    }

}
}
