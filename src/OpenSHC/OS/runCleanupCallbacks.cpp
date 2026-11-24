#include "../OS.func.hpp"

namespace OpenSHC {
namespace CrtStatics {

    // FUNCTION: STRONGHOLDCRUSADER 0x0057EC4D
    void __fastcall runCleanupCallbacks(void*)
    {
        typedef void (__cdecl* Callback)();
        const unsigned count = 10;
        Callback* callbacks = reinterpret_cast<Callback*>(Address::SHC_3BB0A8C1_0x02427598 - count * sizeof(Callback));
        unsigned& next = *reinterpret_cast<unsigned*>(Address::SHC_3BB0A8C1_0x00B94154);
        // Advance the shared index before the callback, which can reenter cleanup.
        for (; next < count;) {
            Callback callback = callbacks[next++];
            if (callback)
                callback();
        }
    }

} // namespace CrtStatics
} // namespace OpenSHC
