#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00471690
    int TextManager::computeTextWidth(char* text, int fontSize)
    {
        char* _textRunPtr;
        int _width;
        char _currentChar;
        if (text == (char*)0x0) {
            return 0;
        }
        _textRunPtr = text;
        do {
            _currentChar = *_textRunPtr;
            _textRunPtr = _textRunPtr + 1;
        } while (_currentChar != '\0');
        _width = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getWidthOfText,
            &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(text, (int)_textRunPtr - (int)(text + 1));
        return _width;
    }

}
}
