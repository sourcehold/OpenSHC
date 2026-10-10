#include "../TextEditorState.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F0D0
    void TextEditorState::helpToken_insertSpaceForHelpTextToken(HelpTextToken token)
    {
        int iVar1;
        iVar1 = MACRO_CALL_MEMBER(Text::TextEditorState_Func::helpToken_getHelpTokenAdvanceLength, this)(token);
        if (this->activeHelpHotspotIndex <= this->customHelpTextLength) {
            int iVar3 = (this->customHelpTextLength + iVar1) * 2;
            int iVar2 = this->customHelpTextLength;
            do {
                *(WCHAR*)(iVar3 + (int)this->DAT_PointerToTemporaryTextMemory)
                    = this->DAT_PointerToTemporaryTextMemory[iVar2];
                iVar2 = iVar2 + -1;
                iVar3 = iVar3 + -2;
            } while (this->activeHelpHotspotIndex <= iVar2);
        }
        this->customHelpTextLength = this->customHelpTextLength + iVar1;
    }

}
}
