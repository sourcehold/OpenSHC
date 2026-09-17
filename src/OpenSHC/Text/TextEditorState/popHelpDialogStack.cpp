#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00462150
    void TextEditorState::popHelpDialogStack()
    {
        int sectionId = this->helpSectionHistoryStack[0];

        for (int i = 0; i < 29; ++i) {
            this->helpSectionHistoryStack[i] = this->helpSectionHistoryStack[i + 1];
        }
        this->helpSectionHistoryStack[29] = -1;

        this->currentHelpSectionID = sectionId;
        if (sectionId == -1) {
            MACRO_CALL_MEMBER(TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
        } else {
            MACRO_CALL_MEMBER(TextEditorState_Func::loadAndLayoutHelpContent, this)();
        }
    }

}
}
