#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004245D0
    void TextManager::renderMultilineText4Unk(eTextSections textOffsetIndex, int textNumInGroup, int xPos, int yPos,
        int maxWidth, uint color, int fontSize, int blendStrength)
    {
        this->field_0x30 = 1;
        MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText5Unk, this)(
            MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(textOffsetIndex, textNumInGroup),
            xPos, yPos, maxWidth, color, fontSize, blendStrength);
    }

}
}
