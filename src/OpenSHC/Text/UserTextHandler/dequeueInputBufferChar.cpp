#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004699E0
    uint UserTextHandler::dequeueInputBufferChar()
    {
        if (this->inputBufferIndex == 0) {
            return 0xffffffff;
        }

        uint const dequeued = (uint)(byte)this->inputBuffer[0];
        for (int i = 0; i < this->inputBufferIndex - 1; ++i) {
            this->inputBuffer[i] = this->inputBuffer[i + 1];
        }
        this->inputBufferIndex = this->inputBufferIndex - 1;
        return dequeued;
    }

}
}
