#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/PlayerInfoOnHoverDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C5C0
    void Init::CreatePlayerInfoOnHoverDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, PlayerInfoOnHoverDisplayElement::ptr)(
            DE::SHCDE::OST_WHO_OWNS, 400, 430, 0,
            UI::DisplayElements_Func::RenderPlayerInfoOnHoverDisplayElement::get(), UI::Enums::DEPM_TOWARDS_MID_Y);
    }

}
}
