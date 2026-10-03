#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::TextArrayIndexType;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      param_1 is 0xb if Exit Crusader or Restart Game, 0xC if Options   decompilerscript: committed: 2025-01-30
      21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004916C0
    void MenuTextInputState::activateModalDialogAndClearText(MenuModalType dialogID)
    {
        if (this->currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
            this->DAT_SomeTextArrayIndex = DAT_UserTextHandlerState::instance.textArrayIndex;
            DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
            if (DAT_UserTextHandlerState::instance.textArrayIndex != OpenSHC::Text::TAIT_ZERO) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
            }
        }
        if (this->currentModalDialog != dialogID) {
            this->modalDialog_6 = this->modalDialog_5;
            this->modalDialog_5 = this->modalDialog_4;
            this->modalDialog_4 = this->modalDialog_3;
            this->modalDialog_3 = this->modalDialog_2;
            this->modalDialog_2 = this->currentModalDialog;
            this->currentModalDialog = dialogID;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(dialogID, TRUE);
        }
    }

}
}
