#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00491750
    void MenuTextInputState::clearAnyOtherModalDialogs()
    {
        DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
            this->DAT_SomeTextArrayIndex);
        if (this->DAT_SomeTextArrayIndex != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
        }
        this->currentModalDialog = OpenSHC::UI::Enums::MMT_NO_MENU;
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
            OpenSHC::UI::Enums::MMT_NONE, TRUE);
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::clearModalDialog2to6, this)();
        if (this->field42_0x9c != 0) {
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
        }
        this->field42_0x9c = 0;
    }

}
}
