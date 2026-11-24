#include "../Meta.func.hpp"

namespace OpenSHC {
namespace CrtStatics {
    void __fastcall runCleanupCallbacks(void* object);
}

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7E8
void Meta::Destructor_0059d7e8()
{
    char* const locks2 = reinterpret_cast<char*>(Address::SHC_3BB0A8C1_0x02427598);
    // The cleanup sentinel immediately follows the second lock object.
    CrtStatics::runCleanupCallbacks(locks2 + 1);
}

} // namespace OpenSHC
