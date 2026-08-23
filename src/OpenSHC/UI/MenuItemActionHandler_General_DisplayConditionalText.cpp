#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004F6A60
void UI::MenuItemActionHandler_General_DisplayConditionalText(int param_1, ...)
{
    MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::renderCurrentlyDisplayedTextConstructionCost,
        DAT_BottomLeftTextDisplayState::ptr)(param_1);
}

}
