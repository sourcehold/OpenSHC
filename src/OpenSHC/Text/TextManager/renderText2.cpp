#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004243E0
    void TextManager::renderText2(eTextSections textOffsetIndex, int textNumInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderTextToScreen, this)(
            MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(textOffsetIndex, textNumInGroup),
            xParam, yParam, alignment, color, fontSize, keepOffsetX, 0);
    }

}
}
