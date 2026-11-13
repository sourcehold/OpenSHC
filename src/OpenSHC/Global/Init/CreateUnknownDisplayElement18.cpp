#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement18.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C400
    void Init::CreateUnknownDisplayElement18()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement18::ptr)(
            (DE::SHCDE::eOnScreenText)18, 200, 4, 1, (UI::DisplayElementRenderFunc*)Global_Func::DoNothing::get(),
            (UI::Enums::DisplayElementPositionModifier)5);
    }

}
}
