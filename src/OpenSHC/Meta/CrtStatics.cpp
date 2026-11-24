#include "CrtStatics.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace CrtStatics {

    // Four critical sections are followed by the first one-byte _Init_locks object.
    static const unsigned lockCount = 4;
    static CRITICAL_SECTION* const lockTable = reinterpret_cast<CRITICAL_SECTION*>(
        Address::SHC_3BB0A8C1_0x024274E0 - lockCount * sizeof(CRITICAL_SECTION));
    static LONG* const lockUsers = reinterpret_cast<LONG*>(Address::SHC_3BB0A8C1_0x00B94074);
    typedef void (__cdecl* MutexFunction)(CRITICAL_SECTION*);

    // FUNCTION: STRONGHOLDCRUSADER 0x0057E2EA
    void* __fastcall constructLocks(void* object)
    {
        if (InterlockedIncrement(lockUsers) == 0) {
            for (unsigned i = 0; i < lockCount; ++i)
                reinterpret_cast<MutexFunction>(&trampoline<Address::SHC_3BB0A8C1_0x0057EC01>)(&lockTable[i]);
        }
        return object;
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0057E319
    void __fastcall destroyLocks(void*)
    {
        if (InterlockedDecrement(lockUsers) < 0) {
            for (unsigned i = 0; i < lockCount; ++i)
                reinterpret_cast<MutexFunction>(&trampoline<Address::SHC_3BB0A8C1_0x0057EC0C>)(&lockTable[i]);
        }
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x00467730
    void __fastcall destroyLocale(void* object)
    {
        struct Facet {
            void (__thiscall** vtable)(Facet*, unsigned);
            unsigned refs;
        };
        Facet* facet = *static_cast<Facet**>(object);
        if (facet) {
            int lock;
            typedef void (__thiscall* Acquire)(int*, int);
            typedef void (__thiscall* Release)(int*);
            reinterpret_cast<Acquire>(&trampoline<Address::SHC_3BB0A8C1_0x0057E342>)(&lock, 0);
            if (facet->refs != 0 && facet->refs != ~0u)
                --facet->refs;
            bool destroy = facet->refs == 0;
            reinterpret_cast<Release>(&trampoline<Address::SHC_3BB0A8C1_0x0057E363>)(&lock);
            if (destroy)
                facet->vtable[0](facet, 1);
        }
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0057EC4D
    void __fastcall runCleanupCallbacks(void*)
    {
        typedef void (__cdecl* Callback)();
        const unsigned count = 10;
        Callback* callbacks = reinterpret_cast<Callback*>(Address::SHC_3BB0A8C1_0x02427598 - count * sizeof(Callback));
        unsigned& next = *reinterpret_cast<unsigned*>(Address::SHC_3BB0A8C1_0x00B94154);
        while (next < count) {
            Callback callback = callbacks[next++];
            if (callback)
                callback();
        }
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x00580CDF
    void __fastcall destroyException(void* object)
    {
        struct Exception {
            void* vtable;
            char* message;
            int ownsMessage;
        };
        Exception* ex = static_cast<Exception*>(object);
        ex->vtable = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x005AC238);
        if (ex->ownsMessage)
            MACRO_CALL(OS_Func::_free_base)(ex->message);
    }

} // namespace CrtStatics
} // namespace OpenSHC
