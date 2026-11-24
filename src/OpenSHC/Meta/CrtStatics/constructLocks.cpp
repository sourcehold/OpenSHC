#include "../CrtStatics.hpp"

#include "LockTable.hpp"

namespace OpenSHC {
namespace CrtStatics {

    // FUNCTION: STRONGHOLDCRUSADER 0x0057E2EA
    void* __fastcall constructLocks(void* object)
    {
        if (InterlockedIncrement(lockUsers) == 0) {
            for (unsigned i = 0; i < lockCount; ++i)
                reinterpret_cast<MutexFunction>(&trampoline<Address::SHC_3BB0A8C1_0x0057EC01>)(&lockTable[i]);
        }
        return object;
    }

} // namespace CrtStatics
} // namespace OpenSHC
