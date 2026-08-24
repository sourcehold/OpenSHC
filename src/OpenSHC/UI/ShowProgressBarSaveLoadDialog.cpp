#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuModalType;

/*
  Sets DAT_MenuOptionsActionParameter to a value derived from param_1 (0x20 or 0x2e), activates the
   MMT_PROGRESS_BAR_BOX modal dialog and immediately calls
   MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic(0). Entry point for triggering
   the save/load progress bar UI.

   renamed by: Claude Sonnet 4.6
 */

// FUNCTION: STRONGHOLDCRUSADER 0x00495800
void UI::ShowProgressBarSaveLoadDialog(int param_1)

{
    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = (-(uint)(param_1 != 0) & 0xe) + 0x20;
    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog2, DAT_MenuModalComposition1::ptr)(
        OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX);
    DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX;
    MACRO_CALL(OpenSHC::UI_Func::MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic)(0);
    return;
}

}
