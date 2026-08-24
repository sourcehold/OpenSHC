#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x0043F2C0
void UI::MenuItemRenderFunction_BuildingAndStatusMenu_PopularityMenuSwitchButton(int param_1, ...)

{
    if (DAT_GameCore::instance.field78_0x148 != 1) {
        if (DAT_GameCore::instance.field77_0x144 == 1) {
            DAT_CurrentButtonGmDataIndex::instance = 0x73;
        }
        MACRO_CALL(OpenSHC::UI_Func::
                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        return;
    }
    return;
}

}
