#include "OpenSHC/Text/TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00461550
    void TextEditorState::renderHelpDialogIfOpen()
    {
        if (this->isDialogStateInitialized != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::drawHelpWindowBackground, this)();
            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, this)();
        }
    }

}
}
