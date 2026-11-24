#include "../Meta.func.hpp"
#include "CrtStatics.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7DE
void Meta::Destructor_0059d7de()
{
    CrtStatics::destroyLocks(CrtStatics::locks2);
}

} // namespace OpenSHC
