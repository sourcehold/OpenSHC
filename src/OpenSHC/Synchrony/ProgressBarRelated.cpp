#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuModalType;

// FUNCTION: STRONGHOLDCRUSADER 0x00495840
void Synchrony::ProgressBarRelated()
{
    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x1f;
    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog2, DAT_MenuModalComposition1::ptr)(
        OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX);
    MACRO_CALL(OpenSHC::UI_Func::MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic)(0);
}

}
