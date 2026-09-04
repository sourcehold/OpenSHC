#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x00494920
void UI::MenuItemActionHandler_SaveMap_ReturnKeySave(int param_1, ...)

{
    bool bVar1;

    bVar1 = DAT_UserTextHandlerState::instance.returnPressed != 0;
    DAT_UserTextHandlerState::instance.returnPressed = 0;
    if (bVar1) {
        MACRO_CALL(OpenSHC::UI_Func::MenuItemActionHandler_SaveLoadMap_Buttons)(3);
        return;
    }
    return;
}

}
