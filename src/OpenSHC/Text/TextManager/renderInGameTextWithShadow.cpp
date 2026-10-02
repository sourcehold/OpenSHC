#include "../TextManager.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00475E00
    void TextManager::renderInGameTextWithShadow(char const* textAddress, int xParam, int yParam,
        TextAlignment alignment, uint foregroundColor, uint backgroundColor, int fontSize, BOOLEnum keepOffsetX,
        int blendStrength)
    {
        int iVar2 = this->field9_0x24;
        int iVar1 = this->currentXOffset_0x0;
        this->field11_0x2c = 1;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)((char*)textAddress, xParam, yParam,
            alignment, (BGR24)((int)(backgroundColor)), fontSize, keepOffsetX, blendStrength);
        this->field10_0x28 = iVar2;
        this->currentXOffset_0x0 = iVar1;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, this)((char*)textAddress, xParam + -2,
            yParam + -1, alignment, (BGR24)((int)(foregroundColor)), fontSize, keepOffsetX, blendStrength);
        this->field11_0x2c = 0;
        return;
    }

}
}
