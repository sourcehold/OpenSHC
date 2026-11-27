#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00474390
    void TextManager::renderNumber2(int integer, int xPosition, int yPosition, TextAlignment textShift, uint color,
        uint param_6, int fontSize, BOOLEnum param_8, int param_9)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::fillIntegerTextBuffer, this)(integer);
        int const savedXOffset = this->currentXOffset_0x0;
        int const savedField24 = this->field_0x24;
        this->drawingTextShadow = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)(this->integerTextBuffer, xPosition,
            yPosition, textShift, (BGR24)((int)(param_6)), fontSize, param_8, param_9);
        this->currentXOffset_0x0 = savedXOffset;
        this->field_0x28 = savedField24;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)(this->integerTextBuffer,
            xPosition + -1, yPosition + -1, textShift, (BGR24)((int)(color)), fontSize, param_8, param_9);
        this->drawingTextShadow = 0;
        return;
    }

}
}
