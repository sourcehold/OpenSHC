#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_HighlightedSkirmishType.hpp"

namespace OpenSHC {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x0042C060
void UI::MenuItemRenderFunction_SelectCrusade_Main(int param_1, ...)

{
    if (param_1 == -1) {
        DAT_HighlightedSkirmishType::instance = 0;
    }
    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
        DAT_HighlightedSkirmishType::instance = param_1;
    }
    MACRO_CALL(
        OpenSHC::UI_Func::MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
    return;
}

}
