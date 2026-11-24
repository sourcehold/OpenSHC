#pragma once

// These objects and their cleanup routines belong to the game's statically linked CRT.
namespace OpenSHC {
namespace CrtStatics {

    static void* const locks = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x024274E0);
    static void* const localeState = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x02427504);
    static char* const locks2 = reinterpret_cast<char*>(Address::SHC_3BB0A8C1_0x02427598);
    static void** const exceptionObject = reinterpret_cast<void**>(Address::SHC_3BB0A8C1_0x024275A8);
    static void* const badAllocVtable = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x005A59B0);

    void* __fastcall constructLocks(void* object);
    void __fastcall destroyLocks(void* object);
    void __fastcall destroyLocale(void* object);
    void __fastcall runCleanupCallbacks(void* object);
    void __fastcall destroyException(void* object);

} // namespace CrtStatics
} // namespace OpenSHC
