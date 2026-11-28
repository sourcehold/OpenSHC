#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424650
    void TextManager::renderLeftAlignedNumberToScreen(
        int number, int xParam, int yParam, uint color, int fontSize, BOOL keepOffsetX)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderNumberToScreen2, this)(
            number, xParam, yParam, TTA_LEFT, color, fontSize, keepOffsetX, 0);
    }

}
}
