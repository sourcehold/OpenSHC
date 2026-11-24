#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/Meta/CrtStatics.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CCE6
    void Init::Constructor_Locks()
    {
        CrtStatics::constructLocks(CrtStatics::locks);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d7ca::get());
    }

} // namespace Global
} // namespace OpenSHC
