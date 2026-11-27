#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424420
    void TextManager::renderInGameText2(eTextSections textOffsetIndex, int textNumInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, this)(
            MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(textOffsetIndex, textNumInGroup),
            xParam, yParam, alignment, color1, color2, fontSize, keepOffsetX, blendStrength);
    }

}
}
