#include "../Meta.func.hpp"
#include "CrtStatics.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7D4
void Meta::Destructor_0059d7d4()
{
    CrtStatics::destroyLocale(CrtStatics::localeState);
}

} // namespace OpenSHC
