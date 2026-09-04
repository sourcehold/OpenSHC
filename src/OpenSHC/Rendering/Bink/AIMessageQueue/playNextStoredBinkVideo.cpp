#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004C62A0
        void AIMessageQueue::playNextStoredBinkVideo()
        {
            if (this->messagePlaying_0x0 != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playNextStoredAIMessage, this)();
            }
            this->storedMessages_0x924 = 0;
        }

    }
}
}
