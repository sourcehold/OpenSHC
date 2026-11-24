#include "../Meta.func.hpp"
#include "CrtStatics.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7F2
void Meta::Destructor_0059d7f2()
{
    *CrtStatics::exceptionObject = CrtStatics::badAllocVtable;
    CrtStatics::destroyException(CrtStatics::exceptionObject);
}

} // namespace OpenSHC
