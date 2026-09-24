#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004650A0
    void Helpers::CheckIfEnoughGoldForMonk()
    {
        DAT_EnoughGoldForRequestedUnit::instance
            = 10 <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[0xf];
    }

}
}
