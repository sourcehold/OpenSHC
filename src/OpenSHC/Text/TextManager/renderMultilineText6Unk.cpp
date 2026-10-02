#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00473AC0
    void TextManager::renderMultilineText6Unk(
        char* text, int xPos, int yPos, int maxWidth, uint color1, uint color2, int fontSize, int blendStrength)
    {
        int iVar1 = this->field9_0x24;
        if (text == (char*)0x0) {
            this->field12_0x30 = (dword)text;
            return;
        }
        this->field11_0x2c = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(
            text, xPos, yPos, maxWidth, color2, blendStrength, 0);
        this->field10_0x28 = iVar1;
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(
            text, xPos + -2, yPos + -1, maxWidth, color1, blendStrength, 0);
        this->field11_0x2c = 0;
        this->field12_0x30 = 0;
        return;
    }

}
}
