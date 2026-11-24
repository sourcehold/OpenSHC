#include "../Meta.func.hpp"
#include "CrtStatics.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7E8
void Meta::Destructor_0059d7e8()
{
    // The cleanup sentinel immediately follows the second lock object.
    CrtStatics::runCleanupCallbacks(CrtStatics::locks2 + 1);
}

} // namespace OpenSHC
