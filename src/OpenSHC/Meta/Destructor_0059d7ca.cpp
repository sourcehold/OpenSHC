#include "../Meta.func.hpp"
#include "CrtStatics.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7CA
void Meta::Destructor_0059d7ca()
{
    CrtStatics::destroyLocks(CrtStatics::locks);
}

} // namespace OpenSHC
