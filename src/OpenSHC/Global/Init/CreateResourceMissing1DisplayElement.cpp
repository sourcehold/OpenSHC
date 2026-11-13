#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/ResourceMissing1DisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C480
    void Init::CreateResourceMissing1DisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, ResourceMissing1DisplayElement::ptr)(
            DE::SHCDE::OST_FEEDBACK_1, 10, 403, 0,
            UI::DisplayElements_Func::RenderResourceMissing1DisplayElement::get(),
            (UI::Enums::DisplayElementPositionModifier)6);
    }

}
}
