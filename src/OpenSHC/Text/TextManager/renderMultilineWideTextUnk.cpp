#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00473B50
    void TextManager::renderMultilineWideTextUnk(
        LPWSTR _wideText, int xPos, int yPos, int maxWidth, uint color1, uint color2, int fontSize, int blendStrength)
    {
        if (_wideText == NULL) {
            this->field_0x30 = 0;
            return;
        }
        int const savedField24 = this->field_0x24;
        this->drawingTextShadow = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineWideTextUnk,
            &this->fontSizeClassArray[fontSize])(_wideText, xPos, yPos, maxWidth, color2, blendStrength, 0);
        this->field_0x28 = savedField24;
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineWideTextUnk,
            &this->fontSizeClassArray[fontSize])(_wideText, xPos - 2, yPos - 1, maxWidth, color1, blendStrength, 0);
        this->drawingTextShadow = 0;
        this->field_0x30 = 0;
    }

}
}
