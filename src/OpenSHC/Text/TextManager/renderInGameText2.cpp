#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00424420
    void TextManager::renderInGameText2(eTextSections textOffsetIndex, int textNumInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color1, uint color2, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        char* textAddress;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, this)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                textOffsetIndex, textNumInGroup),
            xParam, yParam, alignment, color1, color2, fontSize, keepOffsetX, blendStrength);
        return;
    }

}
}
