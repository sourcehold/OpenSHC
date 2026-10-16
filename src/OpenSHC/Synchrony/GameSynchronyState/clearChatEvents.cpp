#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047F7E0
    void GameSynchronyState::clearChatEvents()
    {
        int* _chatEventPtr;
        int _chatEventCounter;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            0xfa, '\0', (void*)((int)(this->receivedChatMessage)));
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            5000, '\0', (void*)((int)(this->DAT_ChatMessageArray)));
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            5000, '\0', (void*)((int)(this->DAT_ChatMessageSubjectPlayerNameArray)));
        this->DAT_ChatMessageArrayIndex = 0;
        _chatEventPtr = &this->DAT_ChatEventArray[0].time;
        _chatEventCounter = 0x14;
        do {
            _chatEventPtr[-1] = 0;
            _chatEventPtr[0] = 0;
            _chatEventPtr[1] = 0;
            _chatEventPtr = _chatEventPtr + 4;
            _chatEventCounter = _chatEventCounter + -1;
        } while (_chatEventCounter);
        this->chatScrollOffset = 0;
    }

}
}
