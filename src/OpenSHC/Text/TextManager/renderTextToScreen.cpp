#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00474250
    void TextManager::renderTextToScreen(char const* textAddress, int xPos, int yPos, TextAlignment alignment,
        BGR24 color, int fontSize, BOOLEnum keepXOffset, int blendStrength)
    {
        if (keepXOffset == FALSE) {
            this->currentXOffset_0x0 = 0;
        }
        if (textAddress == NULL) {
            return;
        }
        int const textWidth = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfText,
            &this->fontSizeClassArray[fontSize])(const_cast<char*>(textAddress), strlen(textAddress));
        if (alignment > 0) {
            xPos += (alignment - textWidth) / 2;
        } else if (alignment < 0) {
            xPos -= textWidth;
        } else {
            xPos += this->currentXOffset_0x0;
        }
        this->currentXOffset_0x0 += textWidth;
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderText, &this->fontSizeClassArray[fontSize])(
            const_cast<char*>(textAddress), strlen(textAddress), xPos, yPos, color, blendStrength);
    }

}
}
