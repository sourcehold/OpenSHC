#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00424360
    void TextManager::renderTextToScreen2(char* textAddress, int xParam, int yParam, TextAlignment alignment,
        BGR24 color, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(TextManager_Func::renderTextToScreen, this)(
            textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, 0);
    }

}
}
