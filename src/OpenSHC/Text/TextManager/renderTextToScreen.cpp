#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00474250
    void TextManager::renderTextToScreen(char const* text, int xPos, int yPos, TextAlignment alignment, BGR24 color,
        int fontSize, BOOLEnum keepXOffset, int blendStrength)
    {
        if (keepXOffset == FALSE) {
            this->currentXOffset_0x0 = 0;
        }
        if (text == NULL) {
            return;
        }
        int const textWidth = MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfText,
            &this->fontSizeClassArray[fontSize])(const_cast<char*>(text), strlen(text));
        // xPos is adjusted in place: computing the position into a separate local does not match
        if (alignment > 0) {
            xPos += (alignment - textWidth) / 2;
        } else if (alignment < 0) {
            xPos -= textWidth;
        } else {
            xPos += this->currentXOffset_0x0;
        }
        this->currentXOffset_0x0 += textWidth;
        MACRO_CALL_MEMBER(FontSizeClass_Func::renderText, &this->fontSizeClassArray[fontSize])(
            const_cast<char*>(text), strlen(text), xPos, yPos, color, blendStrength);
    }

}
}
