#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F080
    int TextEditorState::helpToken_getHelpTokenAdvanceLength(HelpTextToken token)
    {
        switch (token) {
        case HTT_PIC:
            return 4;

        case HTT_FONT:
        case HTT_COLOUR:
        case HTT_LINK:
        case HTT_LINKCOLOUR:
        case HTT_SOUND:
        case HTT_STRING:
        case HTT_INCLUDE:
            return 3;

        default:
            return 1;
        }
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F0D0
    void TextEditorState::helpToken_insertSpaceForHelpTextToken(HelpTextToken token)
    {
        int tokenLength = MACRO_CALL_MEMBER(TextEditorState_Func::helpToken_getHelpTokenAdvanceLength, this)(token);
        for (int textIndex = this->customHelpTextLength; textIndex >= this->activeHelpHotspotIndex; --textIndex) {
            this->DAT_PointerToTemporaryTextMemory[textIndex + tokenLength]
                = this->DAT_PointerToTemporaryTextMemory[textIndex];
        }
        this->customHelpTextLength += tokenLength;
    }

}
}
