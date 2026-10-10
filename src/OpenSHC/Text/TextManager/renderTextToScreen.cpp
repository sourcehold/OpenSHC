#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00474250
    void TextManager::renderTextToScreen(char* textAddress, int xParam, int yParam, TextAlignment alignment,
        BGR24 color, int fontSize, BOOLEnum keepOffsetX, int blendStrength)
    {
        char* _textLengthHelper;
        int _textWidth;
        int xPos;
        char _char;
        if (!keepOffsetX) {
            this->currentXOffset_0x0 = 0;
        }
        if (textAddress != (char*)0x0) {
            _textLengthHelper = textAddress;
            do {
                _char = *_textLengthHelper;
                _textLengthHelper = _textLengthHelper + 1;
            } while (_char != '\0');
            _textWidth = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::getWidthOfText,
                &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(
                textAddress, (int)_textLengthHelper - (int)(textAddress + 1));
            if ((int)alignment <= 0) {
                if ((int)alignment < 0) {
                    xPos = xParam - _textWidth;
                } else {
                    xPos = xParam + this->currentXOffset_0x0;
                }
            } else {
                xPos = xParam + (int)(alignment - _textWidth) / 2;
            }
            this->currentXOffset_0x0 = this->currentXOffset_0x0 + _textWidth;
            _textLengthHelper = textAddress;
            do {
                _char = *_textLengthHelper;
                _textLengthHelper = _textLengthHelper + 1;
            } while (_char != '\0');
            MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderText,
                &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(
                textAddress, (int)_textLengthHelper - (int)(textAddress + 1), xPos, yParam, color, blendStrength);
        }
        return;
    }

}
}
