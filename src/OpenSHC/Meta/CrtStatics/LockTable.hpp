#pragma once

namespace OpenSHC {
namespace CrtStatics {

    // Four critical sections are followed by the first one-byte _Init_locks object.
    static const unsigned lockCount = 4;
    static CRITICAL_SECTION* const lockTable = reinterpret_cast<CRITICAL_SECTION*>(
        Address::SHC_3BB0A8C1_0x024274E0 - lockCount * sizeof(CRITICAL_SECTION));
    static LONG* const lockUsers = reinterpret_cast<LONG*>(Address::SHC_3BB0A8C1_0x00B94074);
    typedef void (__cdecl* MutexFunction)(CRITICAL_SECTION*);

} // namespace CrtStatics
} // namespace OpenSHC
