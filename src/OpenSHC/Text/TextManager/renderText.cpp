#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424390
    void TextManager::renderText(eTextSections textGroupIndex, int textNumInGroup, int xPosition, int yPosition,
        TextAlignment alignment, uint foregroundColor, uint backgroundColor, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, this)(
            MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(textGroupIndex, textNumInGroup),
            xPosition, yPosition, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX, 0);
    }

}
}
