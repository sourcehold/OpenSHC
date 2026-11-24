#include "../OS.func.hpp"

namespace OpenSHC {
namespace CrtStatics {

    // FUNCTION: STRONGHOLDCRUSADER 0x0057E2EA
    void* __fastcall constructLocks(void* object)
    {
        // Four critical sections are followed by the first one-byte _Init_locks object.
        const unsigned lockCount = 4;
        CRITICAL_SECTION* const lockTable = reinterpret_cast<CRITICAL_SECTION*>(
            Address::SHC_3BB0A8C1_0x024274E0 - lockCount * sizeof(CRITICAL_SECTION));
        LONG* const lockUsers = reinterpret_cast<LONG*>(Address::SHC_3BB0A8C1_0x00B94074);
        typedef void (__cdecl* MutexFunction)(CRITICAL_SECTION*);

        if (InterlockedIncrement(lockUsers) == 0) {
            for (unsigned i = 0; i < lockCount; ++i)
                reinterpret_cast<MutexFunction>(&trampoline<Address::SHC_3BB0A8C1_0x0057EC01>)(&lockTable[i]);
        }
        return object;
    }

} // namespace CrtStatics
} // namespace OpenSHC
