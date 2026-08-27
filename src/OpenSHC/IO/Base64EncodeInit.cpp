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
