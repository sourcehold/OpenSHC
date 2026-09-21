#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004614D0
    void TextEditorState::initializeAndLayoutHelpText()
    {
        for (int i = 0; i < 20000; ++i) {
            this->lineLayoutTable[i].leftBorder = 25;
            this->lineLayoutTable[i].rightBorder = this->dialogContentWidth - 25;
            this->lineLayoutTable[i].unknown2 = 0;
        }
        // Adds vertical space at start
        for (int i = 0; i < 4; ++i) {
            this->lineLayoutTable[i].leftBorder = -1;
        }
        this->imageHotspotCount = 0;
        while (!MACRO_CALL_MEMBER(TextEditorState_Func::processHelpRichTextTokens, this)(0)) {};
    }

}
}
