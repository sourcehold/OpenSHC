#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace CrtStatics {
    void* __fastcall constructLocks(void* object);
}
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CCE6
    void Init::Constructor_Locks()
    {
        void* const locks = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x024274E0);
        CrtStatics::constructLocks(locks);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d7ca::get());
    }

} // namespace Global
} // namespace OpenSHC
