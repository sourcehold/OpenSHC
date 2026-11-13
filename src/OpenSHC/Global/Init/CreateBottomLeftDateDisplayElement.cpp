#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/BottomLeftDateDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C3E0
    void Init::CreateBottomLeftDateDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, BottomLeftDateDisplayElement::ptr)(
            DE::SHCDE::OST_DATE, 4, 424, 0, UI::DisplayElements_Func::RenderBottomLeftDateDisplayElement::get(),
            (UI::Enums::DisplayElementPositionModifier)6);
    }

}
}
