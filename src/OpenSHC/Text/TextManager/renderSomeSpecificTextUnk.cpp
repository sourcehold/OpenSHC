#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00473BE0
    void TextManager::renderSomeSpecificTextUnk(
        int lengthUnk, int otherBlendValueUnk, int xPos, int yPos, uint color, int fontSize)
    {
        MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderSomeSpecificTextUnk,
            &this->fontSizeClassArray[fontSize])(lengthUnk, otherBlendValueUnk, xPos, yPos, color);
    }

}
}
