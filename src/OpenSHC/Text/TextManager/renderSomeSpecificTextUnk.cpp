#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00473BE0
    void TextManager::renderSomeSpecificTextUnk(
        int lengthUnk, int otherBlendValueUnk, int xPos, int yPos, uint color, int fontSize)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderSomeSpecificTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(
            lengthUnk, otherBlendValueUnk, xPos, yPos, color);
        return;
    }

}
}
