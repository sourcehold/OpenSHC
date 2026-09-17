#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004614D0
    void TextEditorState::initializeAndLayoutHelpText()
    {
        for (int i = 0; i < 20000; ++i) {
            this->lineLayoutTable[i].unknown0 = 25;
            this->lineLayoutTable[i].unknown1 = this->dialogContentHeight - 25;
            this->lineLayoutTable[i].unknown2 = 0;
        }
        for (int i = 0; i < 4; ++i) {
            this->lineLayoutTable[i].unknown0 = -1;
        }
        this->imageHotspotCount = 0;
        while (!MACRO_CALL_MEMBER(TextEditorState_Func::processHelpRichTextTokens, this)(0)) {};
    }

}
}
