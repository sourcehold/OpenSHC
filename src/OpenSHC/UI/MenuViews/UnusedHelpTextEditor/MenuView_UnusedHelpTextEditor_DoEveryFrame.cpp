#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
namespace MenuViews {
namespace UnusedHelpTextEditor {

// FUNCTION: STRONGHOLDCRUSADER 0x00440400
void MenuView_UnusedHelpTextEditor_DoEveryFrame()
{
    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::renderHelpDialogIfOpen, DAT_TextEditorState::ptr)();
}

}
}
}
}
