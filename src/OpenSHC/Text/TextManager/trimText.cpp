#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00469F50
    void TextManager::trimText(char* text, int allowedWidth, int fontSize)
    {
        MACRO_CALL_MEMBER(FontSizeClass_Func::wrapTextIntoLines, &this->fontSizeClassArray[fontSize])(
            text, allowedWidth);
    }

}
}
