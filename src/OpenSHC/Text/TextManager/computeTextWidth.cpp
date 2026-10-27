#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471690
    int TextManager::computeTextWidth(char* text, int fontSize)
    {
        if (!text) {
            return 0;
        }
        return MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfText, &this->fontSizeClassArray[fontSize])(
            text, strlen(text));
    }

}
}
