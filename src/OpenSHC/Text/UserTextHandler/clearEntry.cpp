#include "../UserTextHandler.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472BE0
    void UserTextHandler::clearEntry(int textIndex)
    {
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->textArray[textIndex]), 0, this->textArray[textIndex]);
        this->textContentLengthArray[textIndex] = 0;
        this->textCursorIndexArray[textIndex] = 0;
    }

}
}
