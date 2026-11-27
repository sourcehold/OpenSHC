#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00475E00
    void TextManager::renderInGameTextWithShadow(char const* textAddress, int xParam, int yParam,
        TextAlignment alignment, uint foregroundColor, uint backgroundColor, int fontSize, BOOLEnum keepOffsetX,
        int blendStrength)
    {
        int const savedXOffset = this->currentXOffset_0x0;
        int const savedField24 = this->field_0x24;
        this->drawingTextShadow = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)((char*)textAddress, xParam, yParam,
            alignment, (BGR24)((int)(backgroundColor)), fontSize, keepOffsetX, blendStrength);
        this->currentXOffset_0x0 = savedXOffset;
        this->field_0x28 = savedField24;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)((char*)textAddress, xParam + -2,
            yParam + -1, alignment, (BGR24)((int)(foregroundColor)), fontSize, keepOffsetX, blendStrength);
        this->drawingTextShadow = 0;
        return;
    }

}
}
