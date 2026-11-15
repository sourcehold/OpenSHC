#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/GamePausedTextDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C600
    void Init::CreateGamePausedTextDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, GamePausedTextDisplayElement::ptr)(
            DE::SHCDE::OST_GAME_PAUSED, 400, 230, 0,
            UI::DisplayElements_Func::RenderGamePausedTextDisplayElement::get(), UI::Enums::DEPM_MAIN_MENU_X_Y);
    }

}
}
