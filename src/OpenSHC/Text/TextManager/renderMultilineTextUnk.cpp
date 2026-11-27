#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00424500
    void TextManager::renderMultilineTextUnk(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos,
        int maxWidth, uint color, int fontSize, int blendStrength)
    {
        char* text;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, this)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                textOffsetIndex, textNumInGroup),
            xPos, yPos, maxWidth, color, fontSize, blendStrength);
        return;
    }

}
}
