#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00474430
    void TextManager::renderNumberToScreen2(int number, int xParam, int yParam, TextAlignment alignment, uint color,
        int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        MACRO_CALL_MEMBER(TextManager_Func::fillIntegerTextBuffer, this)(number);
        MACRO_CALL_MEMBER(TextManager_Func::renderTextToScreen, this)(
            this->integerTextBuffer, xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
    }

}
}
