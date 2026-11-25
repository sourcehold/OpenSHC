#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004916C0
    void MenuTextInputState::activateModalDialogAndClearText(MenuModalType dialogID)
    {
        if (this->currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
            // Through the global, as the original (this->: quick_diff 1.0000 -> 0.9355)
            DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = DAT_UserTextHandlerState::instance.textArrayIndex;
            DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
            if (DAT_UserTextHandlerState::instance.textArrayIndex != OpenSHC::Text::TAIT_ZERO) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
            }
        }
        if (this->currentModalDialog != dialogID) {
            // Push the current dialog onto the stack (written out per element: quick_diff 1.0000 -> 0.7742)
            for (int i = countof(this->previousModalDialogs) - 1; i > 0; --i) {
                this->previousModalDialogs[i] = this->previousModalDialogs[i - 1];
            }
            this->previousModalDialogs[0] = this->currentModalDialog;
            this->currentModalDialog = dialogID;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(dialogID, TRUE);
        }
    }

}
}
