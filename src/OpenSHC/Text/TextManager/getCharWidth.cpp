#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046A720
    int TextManager::getCharWidth(char character, int fontSize)
    {
        int iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getCharWidthUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[fontSize])(character);
        return iVar1;
    }

}
}
