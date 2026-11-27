#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424470
    void TextManager::renderTextFromTextGroup(eTextSections offsetIndex, int numInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderTextToScreen, this)(
            MACRO_CALL_MEMBER(TextManager_Func::getTextStringInGroupAtOffset, this)(offsetIndex, numInGroup), xParam,
            yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
    }

}
}
