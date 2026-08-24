#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"

namespace OpenSHC {

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004B6500
void UI::MenuItemRenderFunction_InGameMenu_MapEventIconUnk(int param_1, ...)

{
    DAT_ButtonUnknownZero::instance = 1;
    if ((DAT_MinimapViewState::instance.spawnMomentCount != 0) && (DAT_GameCore::instance.isBinkVideoPlaying == 0)) {
        DAT_ButtonUnknownZero::instance = 0;
        MACRO_CALL(OpenSHC::UI_Func::
                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        return;
    }
    return;
}

}
