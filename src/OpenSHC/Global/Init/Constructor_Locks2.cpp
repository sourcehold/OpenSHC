#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace CrtStatics {
    void* __fastcall constructLocks(void* object);
}
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CD08
    void Init::Constructor_Locks2()
    {
        char* const locks2 = reinterpret_cast<char*>(Address::SHC_3BB0A8C1_0x02427598);
        CrtStatics::constructLocks(locks2);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d7de::get());
    }

} // namespace Global
} // namespace OpenSHC
