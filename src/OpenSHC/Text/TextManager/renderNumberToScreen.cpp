#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00424680
    void TextManager::renderNumberToScreen(
        int number, int xParam, int yParam, TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, this)(
            number, xParam, yParam, alignment, color, fontSize, keepOffsetX, 0);
        return;
    }

}
}
