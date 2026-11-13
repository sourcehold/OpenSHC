#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement0.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C3C0
    void Init::CreateUnknownDisplayElement0()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement0::ptr)(
            DE::SHCDE::OST_CHAT, 4, 408, 1, (UI::DisplayElementRenderFunc*)Global_Func::DoNothing::get(),
            (UI::Enums::DisplayElementPositionModifier)6);
    }

}
}
