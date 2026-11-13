#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/DebugNumbersDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C4C0
    void Init::CreateDebugNumbersDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, DebugNumbersDisplayElement::ptr)(
            DE::SHCDE::OST_FRAMERATE, 730, 9, 0, UI::DisplayElements_Func::RenderDebugNumbersDisplayElement::get(),
            (UI::Enums::DisplayElementPositionModifier)9);
    }

}
}
