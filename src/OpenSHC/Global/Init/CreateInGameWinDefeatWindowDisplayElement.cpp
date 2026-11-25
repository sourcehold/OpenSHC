#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/InGameWinDefeatWindowDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C540
    void Init::CreateInGameWinDefeatWindowDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            InGameWinDefeatWindowDisplayElement::ptr)(DE::SHCDE::OST_MP_GAME_OVER, 400, 240, 0,
            UI::DisplayElements_Func::RenderInGameWinDefeatWindowDisplayElement::get(), UI::Enums::DEPM_MAIN_MENU_X_Y);
    }

}
}
