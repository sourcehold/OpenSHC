#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/PeopleLeftToPlaceDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C6E0
    void Init::CreatePeopleLeftToPlaceDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, PeopleLeftToPlaceDisplayElement::ptr)(
            DE::SHCDE::OST_PEOPLE_LEFT, 400, 10, 0,
            UI::DisplayElements_Func::RenderPeopleLeftToPlaceDisplayElement::get(), UI::Enums::DEPM_RESOLUTION_Y);
    }

}
}
