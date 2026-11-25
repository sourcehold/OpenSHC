// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../AIMessageQueue.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BE7E0
        void AIMessageQueue::playEventVideoBik(char* eventText, char* eventVideoBik, char* eventWavFile)
        {
            if (eventText == NULL) {
                return;
            }
            if (this->messagePlaying_0x0) {
                if (this->storedMessages_0x924 == 10) {
                    return;
                }
                this->savedMessageUnknownValue_0x104[this->storedMessages_0x924] = 1;
                this->savedMessageTextPtr_0xdc[this->storedMessages_0x924] = eventText;
                strcpy(this->savedMessageVfxFile_0x12c[this->storedMessages_0x924], eventVideoBik);
                strcpy(this->savedMessageSfxFile_0x514[this->storedMessages_0x924], eventWavFile);
                this->savedMessageUnknownValue2_0x8fc[this->storedMessages_0x924] = 0;
                ++this->storedMessages_0x924;
            } else {
                this->currentMessageText_0x8 = eventText;
                this->currentMessageUnknownValue_0x4 = 1;
                this->currentMessageUnknownValue2_0xd4 = 0;
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playVideoOverMap, this)(
                    eventVideoBik, eventWavFile);
            }
        }

    }
}
}
