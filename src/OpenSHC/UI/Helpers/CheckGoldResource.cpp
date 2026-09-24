#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004650C0
    BOOLEnum Helpers::CheckGoldResource(int param_1)
    {
        int iVar1;

        iVar1 = 0;
        if (param_1 == 5) {
            iVar1 = 0x1e;
        }
        return DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                   .currentResources[0xf]
            >= iVar1;
    }

}
}
