#include "../UserTextHandler.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472B90
    void UserTextHandler::clearTextAndCursor()
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            250, '\0', (void*)((int)(this->textArray + this->textArrayIndex)));
        this->textContentLengthArray[this->textArrayIndex] = 0;
        this->textCursorIndexArray[this->textArrayIndex] = 0;
        this->unknown01 = 1;
        this->returnPressed = 0;
        return;
    }

}
}
