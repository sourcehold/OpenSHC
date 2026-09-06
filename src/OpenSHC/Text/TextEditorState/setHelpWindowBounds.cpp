#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D080
    void TextEditorState::setHelpWindowBounds(undefined4 x, undefined4 y, undefined4 height, undefined4 width)
    {
        this->dialogContentX = x;
        this->dialogContentY = y;
        this->dialogContentHeight = height;
        this->dialogContentWidth = width;
    }

}
}
