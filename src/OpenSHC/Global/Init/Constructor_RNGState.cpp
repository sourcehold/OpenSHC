#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C860
    void Init::Constructor_RNGState()
    {
        MACRO_CALL_MEMBER(Random::RNG_Func::Constructor_RNG, SEC_RNG::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d580::get());
    }

}
}
