#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A720
    int TextManager::getCharWidth(char character, int fontSize)
    {
        return MACRO_CALL_MEMBER(FontSizeClass_Func::getCharWidthUnk, &this->fontSizeClassArray[fontSize])(character);
    }

}
}
