#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00424470
    void TextManager::renderTextFromTextGroup(eTextSections offsetIndex, int numInGroup, int xParam, int yParam,
        TextAlignment alignment, uint color, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        char* _textAddress;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                offsetIndex, numInGroup),
            xParam, yParam, alignment, (BGR24)((int)(color)), fontSize, keepOffsetX, blendStrength);
        return;
    }

}
}
