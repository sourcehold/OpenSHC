// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BE960
        BOOLEnum AIMessageQueue::playNextStoredAIMessage()
        {
            if (this->currentMessageVfxFile_0xc[0] != '\0') {
                MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(
                    1);
            }
            this->mbr_0x928 = 0;
            DAT_GameCore::instance.countdown = 2;
            this->currentMessageVfxFile_0xc[0] = '\0';
            this->currentMessageSfxFile_0x70[0] = '\0';
            this->currentMessageText_0x8 = NULL;
            this->messagePlaying_0x0 = FALSE;
            if (this->storedMessages_0x924) {
                this->currentMessageUnknownValue_0x4 = this->savedMessageUnknownValue_0x104[0];
                // fixme: both arms are identical, but the original keeps them as two blocks (the flag says whether the
                // text is wide, so the source probably differed only in a cast)
                if (!this->savedMessageUnknownValue_0x104[0]) {
                    this->currentMessageText_0x8 = this->savedMessageTextPtr_0xdc[0];
                    this->currentMessageUnknownValue2_0xd4 = this->savedMessageUnknownValue2_0x8fc[0];
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playVideoOverMap, this)(
                        this->savedMessageVfxFile_0x12c[0], this->savedMessageSfxFile_0x514[0]);
                } else {
                    this->currentMessageText_0x8 = this->savedMessageTextPtr_0xdc[0];
                    this->currentMessageUnknownValue2_0xd4 = this->savedMessageUnknownValue2_0x8fc[0];
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playVideoOverMap, this)(
                        this->savedMessageVfxFile_0x12c[0], this->savedMessageSfxFile_0x514[0]);
                }
                // move the remaining messages up the queue
                for (int i = 1; i < this->storedMessages_0x924; ++i) {
                    this->savedMessageUnknownValue_0x104[i - 1] = this->savedMessageUnknownValue_0x104[i];
                    this->savedMessageTextPtr_0xdc[i - 1] = this->savedMessageTextPtr_0xdc[i];
                    strcpy(this->savedMessageVfxFile_0x12c[i - 1], this->savedMessageVfxFile_0x12c[i]);
                    strcpy(this->savedMessageSfxFile_0x514[i - 1], this->savedMessageSfxFile_0x514[i]);
                    this->savedMessageUnknownValue2_0x8fc[i - 1] = this->savedMessageUnknownValue2_0x8fc[i];
                }
                this->storedMessages_0x924 = this->storedMessages_0x924 - 1;
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
