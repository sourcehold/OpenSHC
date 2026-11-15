#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/NoTreeGrowthTextDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C520
    void Init::CreateNoTreeGrowthTextDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, NoTreeGrowthTextDisplayElement::ptr)(
            (DE::SHCDE::eOnScreenText)14, 200, 34, 0,
            UI::DisplayElements_Func::RenderNoTreeGrowthTextDisplayElement::get(), UI::Enums::DEPM_RESOLUTION_Y);
    }

}
}
