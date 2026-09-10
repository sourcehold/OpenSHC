#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00465080
    void Helpers::CheckIfEnoughGoldForLadderman()
    {
        DAT_EnoughGoldForRequestedUnit::instance
            = 4 <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .currentResources[0xf];
    }

}
}
