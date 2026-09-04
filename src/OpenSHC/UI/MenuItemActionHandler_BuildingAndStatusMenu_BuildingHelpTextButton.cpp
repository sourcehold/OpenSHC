#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0043A860
void UI::MenuItemActionHandler_BuildingAndStatusMenu_BuildingHelpTextButton()
{
    if (DAT_BuildingsState::instance.field24_0x18e04c != 0) {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::openBuildingHelpDialog, DAT_TextEditorState::ptr)(
            DAT_BuildingsState::instance.field25_0x18e050);
    }
}

}
