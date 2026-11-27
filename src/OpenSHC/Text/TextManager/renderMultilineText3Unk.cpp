#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424580
    void TextManager::renderMultilineText3Unk(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos,
        int maxWidth, uint color1, uint color2, int fontSize, int blendStrength)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText6Unk, this)(
            MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(textOffsetIndex, textNumInGroup),
            xPos, yPos, maxWidth, color1, color2, fontSize, blendStrength);
    }

}
}
