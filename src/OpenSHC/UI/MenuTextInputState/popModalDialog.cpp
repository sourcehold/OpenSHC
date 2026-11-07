#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00493900
    void MenuTextInputState::popModalDialog()
    {
        MenuModalTypeInt const previousDialog = this->previousModalDialogs[0];
        // Pop the stack (written out per element: quick_diff 0.9394 -> 0.8788)
        for (int i = 0; i < countof(this->previousModalDialogs) - 1; ++i) {
            this->previousModalDialogs[i] = this->previousModalDialogs[i + 1];
        }
        this->previousModalDialogs[countof(this->previousModalDialogs) - 1] = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->currentModalDialog = previousDialog;
        // Guarded, not an early return (an early return for the empty stack: quick_diff 0.9394 -> 0.8788)
        if (previousDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
            if (previousDialog == OpenSHC::UI::Enums::MMT_SAVE_MAP) {
                this->fileListVisibleRowCount = 16;
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_TWO__FILTER_A);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::moveCursorToEnd, DAT_UserTextHandlerState::ptr)();
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)((MenuModalType)previousDialog, TRUE);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, this)();
        }
    }

}
}
