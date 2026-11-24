#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/Meta/CrtStatics.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CD08
    void Init::Constructor_Locks2()
    {
        CrtStatics::constructLocks(CrtStatics::locks2);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d7de::get());
    }

} // namespace Global
} // namespace OpenSHC
