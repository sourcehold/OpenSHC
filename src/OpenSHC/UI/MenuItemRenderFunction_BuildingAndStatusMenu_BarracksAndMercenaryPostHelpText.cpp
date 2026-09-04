#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0043A8C0
void UI::MenuItemRenderFunction_BuildingAndStatusMenu_BarracksAndMercenaryPostHelpText(int param_1, ...)
{
    if (DAT_BuildingsState::instance.field24_0x18e04c != 0) {
        MACRO_CALL(OpenSHC::UI_Func::
                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
    }
}

}
