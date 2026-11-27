#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00424580
    void TextManager::renderMultilineText3Unk(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos,
        int maxWidth, uint color1, uint color2, int fontSize, int blendStrength)
    {
        char* _text;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, this)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                textOffsetIndex, textNumInGroup),
            xPos, yPos, maxWidth, color1, color2, fontSize, blendStrength);
        return;
    }

}
}
