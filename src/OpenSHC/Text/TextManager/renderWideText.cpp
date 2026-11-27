#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004742F0
    void TextManager::renderWideText(LPWSTR wideText, int xPos, int yPos, TextAlignment alignment, uint color,
        int fontSize, BOOL keepXOffset, int blendStrength)
    {
        if (keepXOffset == FALSE) {
            this->currentXOffset_0x0 = 0;
        }
        if (wideText == NULL) {
            return;
        }
        int const textWidth = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfWideText,
            &this->fontSizeClassArray[fontSize])(wideText, wcslen(wideText));
        if (alignment > 0) {
            xPos += (alignment - textWidth) / 2;
        } else if (alignment < 0) {
            xPos -= textWidth;
        } else {
            xPos += this->currentXOffset_0x0;
        }
        this->currentXOffset_0x0 += textWidth;
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderWideText, &this->fontSizeClassArray[fontSize])(
            wideText, wcslen(wideText), xPos, yPos, color, blendStrength);
    }

}
}
