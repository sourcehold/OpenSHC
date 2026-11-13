#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CC90
    void Init::Constructor_Empty2() { MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d7a0::get()); }

}
}
