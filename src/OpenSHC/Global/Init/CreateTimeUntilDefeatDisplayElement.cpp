#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/TimeUntilDefeatDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C6A0
    void Init::CreateTimeUntilDefeatDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, TimeUntilDefeatDisplayElement::ptr)(
            DE::SHCDE::OST_TIMETODEFEAT, 0, 8, 0, UI::DisplayElements_Func::RenderTimeUntilDefeatDisplayElement::get(),
            UI::Enums::DEPM_RESOLUTION_Y);
    }

}
}
