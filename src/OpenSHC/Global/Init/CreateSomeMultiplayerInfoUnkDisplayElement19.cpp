#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/SomeMultiplayerInfoUnkDisplayElement19.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C580
    void Init::CreateSomeMultiplayerInfoUnkDisplayElement19()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            SomeMultiplayerInfoUnkDisplayElement19::ptr)(DE::SHCDE::OST_SPLIT_MESSAGE, 400, 10, 0,
            UI::DisplayElements_Func::RenderSomeMultiplayerInfoUnkDisplayElement19::get(),
            UI::Enums::DEPM_RESOLUTION_Y);
    }

}
}
