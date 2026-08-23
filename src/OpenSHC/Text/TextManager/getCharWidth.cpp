#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A720
    int TextManager::getCharWidth(char character, int fontSize)
    {
        return MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getCharWidthUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(character);
    }

}
}
