#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424680
    void TextManager::renderNumberToScreen(
        int number, int xParam, int yParam, TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderNumberToScreen2, this)(
            number, xParam, yParam, alignment, color, fontSize, keepOffsetX, 0);
    }

}
}
