#include "../UserTextHandler.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472BE0
    void UserTextHandler::clearEntry(int param_1)
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            250, '\0', (void*)((int)(this->textArray + param_1)));
        this->textContentLengthArray[param_1] = 0;
        this->textCursorIndexArray[param_1] = 0;
        return;
    }

}
}
