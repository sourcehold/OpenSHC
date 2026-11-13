#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/SomeMissionNumberUnkDisplayElement9.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C500
    void Init::CreateSomeMissionNumberUnkDisplayElement9()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            SomeMissionNumberUnkDisplayElement9::ptr)((DE::SHCDE::eOnScreenText)9, 290, 225, 0,
            UI::DisplayElements_Func::RenderSomeMissionNumberUnkDisplayElement9::get(), UI::Enums::DEPM_MAIN_MENU_X_Y);
    }

}
}
