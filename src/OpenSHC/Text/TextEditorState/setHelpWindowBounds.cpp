#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D080
    void TextEditorState::setHelpWindowBounds(
        undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
    {
        this->dialogContentX = param_1;
        this->dialogContentY = param_2;
        this->dialogContentHeight = param_3;
        this->dialogContentWidth = param_4;
        return;
    }

}
}
