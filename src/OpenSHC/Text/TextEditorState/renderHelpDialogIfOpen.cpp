#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00461550
    void TextEditorState::renderHelpDialogIfOpen()
    {
        if (this->isDialogStateInitialized) {
            MACRO_CALL_MEMBER(TextEditorState_Func::drawHelpWindowBackground, this)();
            MACRO_CALL_MEMBER(TextEditorState_Func::setTextRenderingLogic, this)();
        }
    }

}
}
