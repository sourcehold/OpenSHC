<<<<<<< HEAD
#include "../IO.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00487080
void IO::Base64EncodeInit(Base64State* state)
{
    state->phase = 0;
    state->carryByte = 0;
    state->lineCharacterCounter = 0;
}

}
=======

#include "OpenSHC/IO/Base64State.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00487080
    void Base64EncodeInit(Base64State* state)
    {
        state->phase = 0;
        *(unsigned char*)&state->carryByte = 0;
        state->lineCharacterCounter = 0;
    }

} // namespace IO
} // namespace OpenSHC
>>>>>>> 29a5686e (batch 2)
