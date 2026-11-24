#include "../Meta.func.hpp"

namespace OpenSHC {
namespace CrtStatics {
    void __fastcall destroyLocale(void* object);
}

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7D4
void Meta::Destructor_0059d7d4()
{
    void* const localeState = reinterpret_cast<void*>(Address::SHC_3BB0A8C1_0x02427504);
    CrtStatics::destroyLocale(localeState);
}

} // namespace OpenSHC
