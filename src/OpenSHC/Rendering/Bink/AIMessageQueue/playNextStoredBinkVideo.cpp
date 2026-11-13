#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x004C62A0
        void AIMessageQueue::playNextStoredBinkVideo()
        {
            if (this->messagePlaying_0x0) {
                MACRO_CALL_MEMBER(AIMessageQueue_Func::playNextStoredAIMessage, this)();
            }
            this->storedMessages_0x924 = 0;
        }

    }
}
}
