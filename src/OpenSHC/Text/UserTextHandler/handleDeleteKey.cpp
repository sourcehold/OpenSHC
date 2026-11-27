#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472D00
    void UserTextHandler::handleDeleteKey()
    {
        if (MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::isTextInputAtCapacity, this)() == 2) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::shiftTextLeftAtCursor, this)(
            this->textCursorIndexArray[this->textArrayIndex],
            this->textContentLengthArray[this->textArrayIndex] - this->textCursorIndexArray[this->textArrayIndex]);
        this->textContentLengthArray[this->textArrayIndex] = strlen(this->textArray[this->textArrayIndex]);
    }

}
}
