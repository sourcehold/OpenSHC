#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuModalType;

// FUNCTION: STRONGHOLDCRUSADER 0x0042AC40
void UI::MenuItemRenderFunction_LobbyMenu_Unknown(int param_1, va_list args)
{
    if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
        MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::renderCurrentlyDisplayedTextConstructionCost,
            DAT_BottomLeftTextDisplayState::ptr)(param_1);
    }
}

}
