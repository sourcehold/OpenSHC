#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"

namespace OpenSHC {
namespace UI {
namespace MenuItems {
namespace General {

// FUNCTION: STRONGHOLDCRUSADER 0x004F6A70
void MenuItemActionHandler_General_RemoveConditionalTextOrReleaseHoverUnk(int param_1, ...)
{
    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::hasPassedCountdownOrDuration,
        DAT_BottomLeftTextDisplayState::ptr)();
}

}
}
}
}
