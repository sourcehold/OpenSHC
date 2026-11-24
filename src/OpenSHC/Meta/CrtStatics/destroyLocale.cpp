#include "../CrtStatics.hpp"

namespace OpenSHC {
namespace CrtStatics {

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

} // namespace CrtStatics
} // namespace OpenSHC
