#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004941F0
void UI::MenuItemActionHandler_NetworkOptions_LeaveButtonUnk(int param_1, va_list args)
{
    if (param_1 == 0x11) {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::popModalDialog, DAT_MenuTextInputState::ptr)();
    }
}

}
