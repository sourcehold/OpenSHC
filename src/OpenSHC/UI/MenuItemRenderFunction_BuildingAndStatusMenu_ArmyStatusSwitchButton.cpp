#include "OpenSHC/UI.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0043FCA0
void UI::MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusSwitchButton()
{
    MACRO_CALL(
        OpenSHC::UI_Func::MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
}

}
