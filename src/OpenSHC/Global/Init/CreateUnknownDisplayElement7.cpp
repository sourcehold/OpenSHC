#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/UnknownDisplayElement7.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C4E0
    void Init::CreateUnknownDisplayElement7()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, UnknownDisplayElement7::ptr)(
            (DE::SHCDE::eOnScreenText)7, 700, 9, 0, UI::DisplayElements_Func::RenderUnknownDisplayElement7::get(),
            (UI::Enums::DisplayElementPositionModifier)9);
    }

}
}
