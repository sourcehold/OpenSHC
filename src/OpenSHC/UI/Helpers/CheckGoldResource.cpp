#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004650C0
    BOOLEnum Helpers::CheckGoldResource(int unitIndex)
    {
        int requiredGold = 0;
        if (unitIndex == 5) {
            requiredGold = 30;
        }
        return DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                   .currentResources[OpenSHC::Game::Resources::RT_GOLD]
            >= requiredGold;
    }

}
}
