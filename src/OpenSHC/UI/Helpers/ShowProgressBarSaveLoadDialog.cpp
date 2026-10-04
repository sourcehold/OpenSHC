#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/ProgressBarBox.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        using OpenSHC::UI::Enums::MenuModalType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00495800
        void ShowProgressBarSaveLoadDialog(int isSaving)
        {
            DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = (isSaving != 0 ? 14 : 0) + 32;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog2,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX);
            DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_PROGRESS_BAR_BOX;
            MACRO_CALL(OpenSHC::UI::MenuItems::ProgressBarBox_Func::
                    MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic)(0);
        }

    }
}
}
