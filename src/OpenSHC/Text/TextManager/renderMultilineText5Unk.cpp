#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00473A70
    void TextManager::renderMultilineText5Unk(
        char* text, int xPos, int yPos, int maxWidth, uint color, int fontSize, int blendStrength)
    {
        if (text != NULL) {
            MACRO_CALL_MEMBER(FontSizeClass_Func::renderMultilineTextUnk, &this->fontSizeClassArray[fontSize])(
                text, xPos, yPos, maxWidth, color, blendStrength, 0);
        }
        this->field_0x30 = 0;
    }

}
}
