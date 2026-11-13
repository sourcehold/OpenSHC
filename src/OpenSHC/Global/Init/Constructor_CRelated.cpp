#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CD1E
    void Init::Constructor_CRelated() { MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d7e8::get()); }

}
}
