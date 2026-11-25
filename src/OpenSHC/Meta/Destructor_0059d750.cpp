#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D750
void Meta::Destructor_0059d750()
{
    ((void(__fastcall*)(LandscapeState*))MACRO_CALL(Global_Func::DoNothing))(DAT_LandscapeState::ptr);
}

}
