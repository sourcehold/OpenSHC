#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004F6A70
void UI::MenuItemActionHandler_General_RemoveConditionalTextOrReleaseHoverUnk(int param_1, va_list args)
{
    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::hasPassedCountdownOrDuration,
        DAT_BottomLeftTextDisplayState::ptr)();
}

}
