#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/GameSpeedTextDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C620
    void Init::CreateGameSpeedTextDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, GameSpeedTextDisplayElement::ptr)(
            DE::SHCDE::OST_GAME_SPEED, 770, 9, 0, UI::DisplayElements_Func::RenderGameSpeedTextDisplayElement::get(),
            UI::Enums::DEPM_MAIN_MENU_X_Y);
    }

}
}
