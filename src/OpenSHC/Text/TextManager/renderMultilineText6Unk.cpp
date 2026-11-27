#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00473AC0
    void TextManager::renderMultilineText6Unk(
        char* text, int xPos, int yPos, int maxWidth, uint color1, uint color2, int fontSize, int blendStrength)
    {
        if (text == NULL) {
            this->field_0x30 = 0;
            return;
        }
        int const savedField24 = this->field_0x24;
        this->drawingTextShadow = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &this->fontSizeClassArray[fontSize])(text, xPos, yPos, maxWidth, color2, blendStrength, 0);
        this->field_0x28 = savedField24;
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &this->fontSizeClassArray[fontSize])(text, xPos - 2, yPos - 1, maxWidth, color1, blendStrength, 0);
        this->drawingTextShadow = 0;
        this->field_0x30 = 0;
    }

}
}
