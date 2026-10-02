#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00469F50
    void TextManager::trimText(char* text, int allowedWidth, int fontSize)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::wrapTextIntoLines,
            &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(text, allowedWidth);
        return;
    }

}
}
