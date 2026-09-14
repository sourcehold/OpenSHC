#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x00469F70
    int TextManager::getTextWidthTillCursorUnk(char* text, int cursorIndex, int fontSize)

    {
        int _widthUnk;

        if (text == (char*)0x0) {
            return 0;
        }
        _widthUnk = MACRO_CALL_MEMBER(
            OpenSHC::Text::FontSizeClass_Func::getWidthOfText, &this->fontSizeClassArray[fontSize])(text, cursorIndex);
        return _widthUnk;
    }

}
}
