#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00493900
    void MenuTextInputState::popModalDialog()
    {
        MenuModalTypeInt _menuModalID;
        _menuModalID = this->modalDialog_2;
        this->modalDialog_2 = this->modalDialog_3;
        this->modalDialog_3 = this->modalDialog_4;
        this->modalDialog_4 = this->modalDialog_5;
        this->modalDialog_5 = this->modalDialog_6;
        this->modalDialog_6 = OpenSHC::UI::Enums::MMT_NO_MENU;
        this->currentModalDialog = _menuModalID;
        if (_menuModalID != OpenSHC::UI::Enums::MMT_NO_MENU) {
            if (_menuModalID == OpenSHC::UI::Enums::MMT_SAVE_MAP) {
                this->field36_0x84 = 0x10;
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    2);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::moveCursorToEnd, DAT_UserTextHandlerState::ptr)();
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)((OpenSHC::UI::Enums::MenuModalType)_menuModalID, TRUE);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, this)();
    }

}
}
