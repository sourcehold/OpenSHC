#include "../MenuTextInputState.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00491750
    void MenuTextInputState::clearAnyOtherModalDialogs()
    {
        DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
            DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex);
        if (DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex != 0) {
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
