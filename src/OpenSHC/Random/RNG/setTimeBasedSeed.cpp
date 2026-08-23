#include "../RNG.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include <time.h>

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A740
    void RNG::setTimeBasedSeed() { this->seed = (__time64_t)MACRO_CALL(OpenSHC::OS_Func::__time64)((__time64_t*)0x0); }

}
}
