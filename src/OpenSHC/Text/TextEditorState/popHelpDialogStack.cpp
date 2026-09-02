#include "../TextEditorState.func.hpp"

#include <string.h>

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00462150
    void TextEditorState::popHelpDialogStack()
    {
        int iVar1 = this->helpSectionHistoryStack[0];
        memcpy(&this->helpSectionHistoryStack[0], &this->helpSectionHistoryStack[1], 29 * sizeof(int));
        this->helpSectionHistoryStack[29] = -1;
        this->currentHelpSectionID = iVar1;
        if (iVar1 == -1) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::loadAndLayoutHelpContent, this)();
    }

}
}
