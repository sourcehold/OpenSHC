#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/ResourceMissing2DisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C4A0
    void Init::CreateResourceMissing2DisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, ResourceMissing2DisplayElement::ptr)(
            DE::SHCDE::OST_FEEDBACK_2, 10, 367, 0,
            UI::DisplayElements_Func::RenderResourceMissing2DisplayElement::get(),
            (UI::Enums::DisplayElementPositionModifier)6);
    }

}
}
