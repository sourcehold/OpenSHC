#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/KeepAndGranaryPlacementInfoDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C5A0
    void Init::CreateKeepAndGranaryPlacementInfoDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            KeepAndGranaryPlacementInfoDisplayElement::ptr)(DE::SHCDE::OST_KEEP_MESSAGE, 725, 447, 0,
            UI::DisplayElements_Func::RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement::get(),
            UI::Enums::DEPM_TOWARDS_MID_Y);
    }

}
}
