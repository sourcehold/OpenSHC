#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004244C0
    int TextManager::renderMultilineText2(eTextSections textOffsetIndex, int textNumInGroup, int maxWidth, int fontSize)
    {
        return MACRO_CALL_MEMBER(
            OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk, &this->fontSizeClassArray[fontSize])(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, this)(
                textOffsetIndex, textNumInGroup),
            0, 0, maxWidth, 0, 0, 1);
    }

}
}
