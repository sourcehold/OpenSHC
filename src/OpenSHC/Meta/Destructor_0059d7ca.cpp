#include "../Meta.func.hpp"

namespace OpenSHC {
namespace CrtStatics {
    void __fastcall destroyLocks(void* object);
}

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7CA
void Meta::Destructor_0059d7ca()
{
    void* const locks = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x024274E0);
    CrtStatics::destroyLocks(locks);
}

} // namespace OpenSHC
