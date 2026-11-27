#include "../UserTextHandler.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472B90
    void UserTextHandler::clearTextAndCursor()
    {
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->textArray[this->textArrayIndex]), 0, this->textArray[this->textArrayIndex]);
        this->textContentLengthArray[this->textArrayIndex] = 0;
        this->textCursorIndexArray[this->textArrayIndex] = 0;
        this->unknown01 = 1;
        this->returnPressed = FALSE;
    }

}
}
