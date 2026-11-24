#include "../CrtStatics.hpp"

#include "LockTable.hpp"

namespace OpenSHC {
namespace CrtStatics {

    // FUNCTION: STRONGHOLDCRUSADER 0x0057E319
    void __fastcall destroyLocks(void*)
    {
        if (InterlockedDecrement(lockUsers) < 0) {
            for (unsigned i = 0; i < lockCount; ++i)
                reinterpret_cast<MutexFunction>(&trampoline<Address::SHC_3BB0A8C1_0x0057EC0C>)(&lockTable[i]);
        }
    }

} // namespace CrtStatics
} // namespace OpenSHC
