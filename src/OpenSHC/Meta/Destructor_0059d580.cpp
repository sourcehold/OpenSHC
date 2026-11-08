#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D580
void Meta::Destructor_0059d580() { ((void(__fastcall*)(RNG*))MACRO_CALL(Global_Func::DoNothing))(SEC_RNG::ptr); }

}
