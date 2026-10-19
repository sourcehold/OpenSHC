#include "../../Synchrony.func.hpp"
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
        this->DAT_ChatMessageArrayIndex = this->DAT_ChatMessageArrayIndex + 1;
        if (20 <= (int)this->DAT_ChatMessageArrayIndex) {
            this->DAT_ChatMessageArrayIndex = 0;
        }
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].subjectPlayer = subjectPlayerID;
        DWORD DVar1 = timeGetTime();
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].time = DVar1;
        /*
          such a weird way to write: DAT_01a22de8
         */
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].flag = 1;
        this->DAT_ChatEventArray[this->DAT_ChatMessageArrayIndex].objectPlayer = objectPlayerID;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(250,
            (void*)((int)(this->receivedChatMessage)),
            (void*)((int)(this->DAT_ChatMessageArray + this->DAT_ChatMessageArrayIndex)));
        if (!subjectPlayerID) {
            /*
              "Host"   added by script: "Host"
             */
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(250,
                (void*)((int)(MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)76, 7))),
                (void*)((int)(this->DAT_ChatMessageSubjectPlayerNameArray + this->DAT_ChatMessageArrayIndex)));
        } else {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(250,
                (void*)((int)(this->DAT_PlayerNames + subjectPlayerID)),
                (void*)((int)(this->DAT_ChatMessageSubjectPlayerNameArray + this->DAT_ChatMessageArrayIndex)));
        }
        if (objectPlayerID) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(250,
                (void*)((int)(this->DAT_PlayerNames + objectPlayerID)),
                (void*)((int)(this->DAT_ChatMessageObjectPlayerNameArray + this->DAT_ChatMessageArrayIndex)));
        }
        this->chatScrollOffset = 0;
    }

}
}
