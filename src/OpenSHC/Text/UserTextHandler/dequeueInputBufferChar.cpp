#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x004699E0
    int UserTextHandler::dequeueInputBufferChar()
    {
        if (!this->inputBufferIndex) {
            return -1;
        }

        int const dequeued = this->inputBuffer[0];
        for (int i = 1; i < this->inputBufferIndex; ++i) {
            this->inputBuffer[i - 1] = this->inputBuffer[i];
        }
        --this->inputBufferIndex;
        return dequeued;
    }

}
}
