#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004742F0
    void TextManager::renderWideText(LPWSTR wideText, int xPos, int yPos, TextAlignment alignment, uint color,
        int fontSize, BOOL keepXOffset, int blendStrength)
    {
        WCHAR WVar1;
        WCHAR* pWVar2;
        int _x;
        if (keepXOffset == 0) {
            this->currentXOffset_0x0 = 0;
        }
        if (wideText != (WCHAR*)0x0) {
            pWVar2 = wideText;
            do {
                WVar1 = *pWVar2;
                pWVar2 = pWVar2 + 1;
            } while (WVar1 != L'\0');
            int _textWidth = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfWideText,
                &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(
                wideText, (int)pWVar2 - (int)(wideText + 1) >> 1);
            if ((int)alignment < 1) {
                if ((int)alignment < 0) {
                    _x = xPos - _textWidth;
                } else {
                    _x = xPos + this->currentXOffset_0x0;
                }
            } else {
                _x = xPos + (int)(alignment - _textWidth) / 2;
            }
            this->currentXOffset_0x0 = this->currentXOffset_0x0 + _textWidth;
            pWVar2 = wideText;
            do {
                WVar1 = *pWVar2;
                pWVar2 = pWVar2 + 1;
            } while (WVar1 != L'\0');
            MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderWideText,
                &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(
                wideText, (int)pWVar2 - (int)(wideText + 1) >> 1, _x, yPos, color, blendStrength);
        }
        return;
    }

}
}
