#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D080
    void TextEditorState::setHelpWindowBounds(int x, int y, int width, int height)
    {
        this->dialogContentX = x;
        this->dialogContentY = y;
        this->dialogContentWidth = width;
        this->dialogContentHeight = height;
    }

}
}
