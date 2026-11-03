#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::TextArrayIndexType;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      dialogID is 0xb for Exit Crusader or Restart Game, 0xc for Options
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004916C0
    void MenuTextInputState::activateModalDialogAndClearText(MenuModalType dialogID)
    {
        if (this->currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
            DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = DAT_UserTextHandlerState::instance.textArrayIndex;
            DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
            if (DAT_UserTextHandlerState::instance.textArrayIndex != OpenSHC::Text::TAIT_ZERO) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
            }
        }
        if (this->currentModalDialog != dialogID) {
            // currentModalDialog and modalDialog_2..6 are a stack of open dialogs; pushing through a pointer
            // keeps the original's loads and stores (the plain fields let the compiler reuse currentModalDialog)
            MenuModalTypeInt* const dialogs = &this->currentModalDialog;
            dialogs[5] = dialogs[4];
            dialogs[4] = dialogs[3];
            dialogs[3] = dialogs[2];
            dialogs[2] = dialogs[1];
            dialogs[1] = dialogs[0];
            dialogs[0] = dialogID;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(dialogID, TRUE);
        }
    }

}
}
