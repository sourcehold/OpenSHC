#include "../TextEditorState.func.hpp"

#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"

#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004620F0
    void TextEditorState::setCustomHelpText(char* helpText, int bufferSize)
    {
        this->customHelpTextPointer = helpText;
        this->isCustomHelpTextWide = 0;
        this->customHelpTextBufferSize = bufferSize;
        MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::multiByteToWideCharacter, DAT_WideCharMultiByteState::ptr)(
            this->DAT_PointerToTemporaryTextMemory, helpText);
        this->customHelpTextLength = strlen(helpText);
        this->isTextHelpDialogMode = TRUE;
        MACRO_CALL_MEMBER(TextEditorState_Func::loadAndLayoutHelpContent, this)();
    }

}
}
