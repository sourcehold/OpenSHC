#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Random/RNG.hpp"
#include <time.h>

namespace OpenSHC {
namespace Random {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A740
    void RNG::setTimeBasedSeed()
    {
        __time64_t time = MACRO_CALL(OpenSHC::OS_Func::__time64)((__time64_t*)0x0);
        this->seed = (int)time;
    }

}
}
