#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004650F0
    void Helpers::CheckIfEnoughGoldForTunneler()
    {
        DAT_EnoughGoldForRequestedUnit::instance
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .currentResources[OpenSHC::Game::Resources::RT_GOLD]
            >= 30;
    }

}
}
