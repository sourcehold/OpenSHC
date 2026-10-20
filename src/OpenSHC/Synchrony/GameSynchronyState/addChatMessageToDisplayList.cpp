#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047F6A0
    void GameSynchronyState::addChatMessageToDisplayList(int subjectPlayerID, int objectPlayerID)
    {
        ++this->DAT_ChatMessageArrayIndex;
        if (20 <= this->DAT_ChatMessageArrayIndex) {
            this->DAT_ChatMessageArrayIndex = 0;
        }
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].subjectPlayer = subjectPlayerID;
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].time = timeGetTime();
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].flag = 1;
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].objectPlayer = objectPlayerID;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(sizeof(this->receivedChatMessage),
            this->receivedChatMessage, this->DAT_ChatMessageArray[this->DAT_ChatMessageArrayIndex]);
        if (!subjectPlayerID) {
            // "Host"
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                sizeof(this->receivedChatMessage),
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    (DE::SHCDE::eTextSections)76, 7),
                this->DAT_ChatMessageSubjectPlayerNameArray[this->DAT_ChatMessageArrayIndex]);
        } else {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                sizeof(this->receivedChatMessage), this->DAT_PlayerNames[subjectPlayerID],
                this->DAT_ChatMessageSubjectPlayerNameArray[this->DAT_ChatMessageArrayIndex]);
        }
        if (objectPlayerID) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                sizeof(this->receivedChatMessage), this->DAT_PlayerNames[objectPlayerID],
                this->DAT_ChatMessageObjectPlayerNameArray[this->DAT_ChatMessageArrayIndex]);
        }
        this->chatScrollOffset = 0;
    }

}
}
