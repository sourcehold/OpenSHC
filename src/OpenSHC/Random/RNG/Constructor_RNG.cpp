#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Random/RNG.hpp"

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471810
    RNG* RNG::Constructor_RNG()

    {
        MACRO_CALL_MEMBER(RNG_Func::setTimeBasedSeed, this)();
        MACRO_CALL_MEMBER(RNG_Func::populateRNG1040, this)();
        return this;
    }

}
}
