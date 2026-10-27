#include "../UserTextHandler.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004715A0
    void UserTextHandler::handleBackspace()
    {
        if (this->textCursorIndexArray[this->textArrayIndex] <= 0) {
            return;
        }
        --this->textCursorIndexArray[this->textArrayIndex];
        MACRO_CALL_MEMBER(UserTextHandler_Func::shiftTextLeftAtCursor, this)(
            this->textCursorIndexArray[this->textArrayIndex],
            this->textContentLengthArray[this->textArrayIndex] - this->textCursorIndexArray[this->textArrayIndex]);
        this->textContentLengthArray[this->textArrayIndex] = strlen(this->textArray[this->textArrayIndex]);
    }

}
}
