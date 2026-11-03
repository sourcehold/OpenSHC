// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BE8A0
        void AIMessageQueue::prepareSFXandVFX(
            char* messageText, char* messageVfxFile, char* messageSfxFile, int param_4)
        {
            if (messageText == NULL) {
                return;
            }
            if (this->messagePlaying_0x0) {
                if (this->storedMessages_0x924 == 10) {
                    return;
                }
                this->savedMessageUnknownValue_0x104[this->storedMessages_0x924] = 1;
                this->savedMessageTextPtr_0xdc[this->storedMessages_0x924] = messageText;
                strcpy(this->savedMessageVfxFile_0x12c[this->storedMessages_0x924], messageVfxFile);
                strcpy(this->savedMessageSfxFile_0x514[this->storedMessages_0x924], messageSfxFile);
                this->savedMessageUnknownValue2_0x8fc[this->storedMessages_0x924] = param_4;
                this->storedMessages_0x924 = this->storedMessages_0x924 + 1;
            } else {
                this->currentMessageText_0x8 = messageText;
                this->currentMessageUnknownValue2_0xd4 = param_4;
                this->currentMessageUnknownValue_0x4 = 1;
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playVideoOverMap, this)(
                    messageVfxFile, messageSfxFile);
            }
        }

    }
}
}
