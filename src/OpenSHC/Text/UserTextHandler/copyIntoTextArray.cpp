// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472C30
    void UserTextHandler::copyIntoTextArray(char const* text)
    {
        MACRO_CALL_MEMBER(UserTextHandler_Func::clearTextAndCursor, this)();
        strcpy(this->textArray[this->textArrayIndex], text);
        this->textContentLengthArray[this->textArrayIndex] = strlen(text);
        this->textCursorIndexArray[this->textArrayIndex] = strlen(text);
        this->unknown01 = 1;
        this->returnPressed = FALSE;
    }

}
}
