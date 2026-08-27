#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00462150
    void TextEditorState::popHelpDialogStack()
    {
        this->currentHelpSectionID = this->helpSectionHistoryStack[0];
        for (int iVar1 = 29; iVar1 != 0; iVar1 = iVar1 + -1) {
            this->helpSectionHistoryStack[iVar1] = this->helpSectionHistoryStack[iVar1 + 1];
        }
        this->helpSectionHistoryStack[29] = -1;
        if (this->helpSectionHistoryStack[0] == -1) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::loadAndLayoutHelpContent, this)();
        return;
    }

}
}
