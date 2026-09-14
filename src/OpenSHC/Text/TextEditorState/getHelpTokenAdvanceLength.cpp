#include "../TextEditorState.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045F080
    undefined4 TextEditorState::getHelpTokenAdvanceLength(undefined4 param_1)
    {
        switch (param_1) {
        case 1:
            return 4;
        case 2:
        case 3:
        case 4:
        case 10:
        case 0xb:
        case 0xc:
        case 0xe:
            return 3;
        default:
            return 1;
        }
    }

}
}
