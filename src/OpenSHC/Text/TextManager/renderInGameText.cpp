#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424320
    void TextManager::renderInGameText(char* textAddress, int xParam, int yParam, TextAlignment alignment, uint color1,
        uint color2, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, this)(
            textAddress, xParam, yParam, alignment, color1, color2, fontSize, keepOffsetX, 0);
    }

}
}
