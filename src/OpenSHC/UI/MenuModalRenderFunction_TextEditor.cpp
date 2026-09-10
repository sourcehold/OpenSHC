#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004AAB40
void UI::MenuModalRenderFunction_TextEditor(int x, int y, int width, int height)
{
    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
}

}
