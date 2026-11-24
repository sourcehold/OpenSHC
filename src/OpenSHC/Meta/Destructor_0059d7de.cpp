#include "../Meta.func.hpp"

namespace OpenSHC {
namespace CrtStatics {
    void __fastcall destroyLocks(void* object);
}

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7DE
void Meta::Destructor_0059d7de()
{
    char* const locks2 = reinterpret_cast<char*>(Address::SHC_3BB0A8C1_0x02427598);
    CrtStatics::destroyLocks(locks2);
}

} // namespace OpenSHC
