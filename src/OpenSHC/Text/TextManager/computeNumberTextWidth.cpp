#include "../TextManager.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004716D0
    int TextManager::computeNumberTextWidth(int numberInt, int fontSize)
    {
        MACRO_CALL_MEMBER(TextManager_Func::fillIntegerTextBuffer, this)(numberInt);
        if (!this->integerTextBuffer) {
            return 0;
        }
        return MACRO_CALL_MEMBER(FontSizeClass_Func::getWidthOfText, &this->fontSizeClassArray[fontSize])(
            this->integerTextBuffer, strlen(this->integerTextBuffer));
    }

}
}
