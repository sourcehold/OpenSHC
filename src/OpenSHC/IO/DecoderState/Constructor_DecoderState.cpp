#include "../DecoderState.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046D140
    DecoderState* DecoderState::Constructor_DecoderState()
    {
        this->implodingType = 0;
        this->implodingTypeSize = 0x1000; // 4096
        return this;
    }

}
}
