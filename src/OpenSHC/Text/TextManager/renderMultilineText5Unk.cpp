#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00473A70
    void TextManager::renderMultilineText5Unk(
        char* text, int xPos, int yPos, int maxWidth, uint color, int fontSize, int blendStrength)
    {
        if (text != (char*)0x0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(
                text, xPos, yPos, maxWidth, color, blendStrength, 0);
        }
        this->field12_0x30 = 0;
        return;
    }

}
}
