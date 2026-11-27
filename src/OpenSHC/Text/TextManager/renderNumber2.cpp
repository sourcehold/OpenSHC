#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00474390
    void TextManager::renderNumber2(int number, int xPosition, int yPosition, TextAlignment alignment,
        uint foregroundColor, uint backgroundColor, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        MACRO_CALL_MEMBER(TextManager_Func::fillIntegerTextBuffer, this)(number);
        // declaration order decides which register holds which value
        int const savedXOffset = this->currentXOffset_0x0;
        int const savedField24 = this->field_0x24;
        this->drawingTextShadow = 1;
        MACRO_CALL_MEMBER(TextManager_Func::renderTextToScreen, this)(this->integerTextBuffer, xPosition, yPosition,
            alignment, backgroundColor, fontSize, keepOffsetX, blendStrength);
        this->currentXOffset_0x0 = savedXOffset;
        this->field_0x28 = savedField24;
        MACRO_CALL_MEMBER(TextManager_Func::renderTextToScreen, this)(this->integerTextBuffer, xPosition - 1,
            yPosition - 1, alignment, foregroundColor, fontSize, keepOffsetX, blendStrength);
        this->drawingTextShadow = 0;
    }

}
}
