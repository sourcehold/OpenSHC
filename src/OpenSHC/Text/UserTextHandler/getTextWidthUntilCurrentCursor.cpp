#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471570
    int UserTextHandler::getTextWidthUntilCurrentCursor()
    {
        return MACRO_CALL_MEMBER(TextManager_Func::getTextWidthTillCursorUnk, DAT_TextManagerObject::ptr)(
            this->textArray[this->textArrayIndex], this->textCursorIndexArray[this->textArrayIndex],
            this->textArrayFontSizes[this->textArrayIndex]);
    }

}
}
