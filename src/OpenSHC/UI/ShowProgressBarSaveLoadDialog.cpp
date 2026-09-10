#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuModalType;

// FUNCTION: STRONGHOLDCRUSADER 0x00495800
void UI::ShowProgressBarSaveLoadDialog(int param_1)
{
    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = (param_1 != 0 ? 0xe : 0) + 0x20;
    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog2, DAT_MenuModalComposition1::ptr)(
        OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX);
    DAT_MenuModalComposition1::instance.activeModalDialogID = Enums::MMT_PROGRESS_BAR_BOX;
    MACRO_CALL(OpenSHC::UI_Func::MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic)(0);
}

}
