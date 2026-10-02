#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004243E0
    void TextManager::renderText2(eTextSections textOffsetIndex, int textNumInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX)
    {
        char* textAddress;
        int blendStrength;
        blendStrength = 0;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                textOffsetIndex, textNumInGroup),
            xParam, yParam, alignment, (BGR24)((int)(color)), fontSize, keepOffsetX, blendStrength);
        return;
    }

}
}
