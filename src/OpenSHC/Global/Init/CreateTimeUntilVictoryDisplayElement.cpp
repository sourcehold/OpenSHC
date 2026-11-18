#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/TimeUntilVictoryDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C660
    void Init::CreateTimeUntilVictoryDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, TimeUntilVictoryDisplayElement::ptr)(
            DE::SHCDE::OST_WIN_TIMER, 0, 8, 0, UI::DisplayElements_Func::RenderTimeUntilVictoryDisplayElement::get(),
            UI::Enums::DEPM_RESOLUTION_Y);
    }

}
}
