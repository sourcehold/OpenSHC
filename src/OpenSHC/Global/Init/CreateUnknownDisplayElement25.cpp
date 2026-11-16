#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement25.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C640
    void Init::CreateUnknownDisplayElement25()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement25::ptr)(
            DE::SHCDE::OST_KING_OF_THE_HILL, 100, 10, 0, UI::DisplayElements_Func::RenderUnknownDisplayElement25::get(),
            UI::Enums::DEPM_RESOLUTION_Y);
    }

}
}
