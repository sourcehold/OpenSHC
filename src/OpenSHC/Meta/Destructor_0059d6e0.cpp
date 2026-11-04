#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D6E0
void Meta::Destructor_0059d6e0()
{
    ((void(__fastcall*)(UnitsState*))MACRO_CALL(Global_Func::DoNothing))(DAT_UnitsState::ptr);
}

}
