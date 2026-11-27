#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00424360
    void TextManager::renderTextToScreen2(char* textAddress, int xParam, int yParam, TextAlignment alignment,
        BGR24 color, int fontSize, BOOLEnum keepOffsetX)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)(
            textAddress, xParam, yParam, alignment, color, fontSize, keepOffsetX, 0);
        return;
    }

}
}
