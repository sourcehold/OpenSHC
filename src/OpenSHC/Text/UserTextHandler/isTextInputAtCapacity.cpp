#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472CB0
    int UserTextHandler::isTextInputAtCapacity()
    {
        int const textWidth = MACRO_CALL_MEMBER(TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            this->textArray[this->textArrayIndex], this->textArrayFontSizes[this->textArrayIndex]);
        if (textWidth >= this->textBoxMaxTextWidthDimensionArray[this->textArrayIndex]) {
            return 2;
        }
        if (this->textCursorIndexArray[this->textArrayIndex] >= this->textBoxMaxCharactersArray[this->textArrayIndex]) {
            return 2;
        }
        return 0;
    }

}
}
