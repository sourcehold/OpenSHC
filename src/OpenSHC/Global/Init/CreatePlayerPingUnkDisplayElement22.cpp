#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/PlayerPingUnkDisplayElement22.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C5E0
    void Init::CreatePlayerPingUnkDisplayElement22()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, PlayerPingUnkDisplayElement22::ptr)(
            DE::SHCDE::OST_PINGS, 660, 40, 0, UI::DisplayElements_Func::RenderPlayerPingUnkDisplayElement22::get(),
            UI::Enums::DEPM_TOWARDS_MID_X);
    }

}
}
