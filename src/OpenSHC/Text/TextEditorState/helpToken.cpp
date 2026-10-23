#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F080
    int TextEditorState::helpToken_getHelpTokenAdvanceLength(HelpTextToken token)
    {
        switch (token) {
        case Enums::HTT_PIC:
            return 4;

        case Enums::HTT_FONT:
        case Enums::HTT_COLOUR:
        case Enums::HTT_LINK:
        case Enums::HTT_LINKCOLOUR:
        case Enums::HTT_SOUND:
        case Enums::HTT_STRING:
        case Enums::HTT_INCLUDE:
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
