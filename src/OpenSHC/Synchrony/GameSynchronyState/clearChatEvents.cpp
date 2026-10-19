#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047F7E0
    void GameSynchronyState::clearChatEvents()
    {
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->receivedChatMessage), '\0', (void*)((int)(this->receivedChatMessage)));
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->DAT_ChatMessageArray), '\0', (void*)((int)(this->DAT_ChatMessageArray)));
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->DAT_ChatMessageSubjectPlayerNameArray), '\0',
            (void*)((int)(this->DAT_ChatMessageSubjectPlayerNameArray)));
        this->DAT_ChatMessageArrayIndex = 0;
        // The original walks one pointer over &DAT_ChatEventArray[0].time and clears the three
        // fields around it with negative and positive indices; objectPlayer stays untouched.
        for (int _chatEvent = 0; _chatEvent < 20; ++_chatEvent) {
            this->DAT_ChatEventArray[_chatEvent].subjectPlayer = 0;
            this->DAT_ChatEventArray[_chatEvent].time = 0;
            this->DAT_ChatEventArray[_chatEvent].flag = 0;
        }
        this->chatScrollOffset = 0;
    }

}
}
