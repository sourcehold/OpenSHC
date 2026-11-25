#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D6D0
void Meta::Destructor_0059d6d0()
{
    ((void(__fastcall*)(PathFindingState*))MACRO_CALL(Global_Func::DoNothing))(DAT_PathFindingState::ptr);
}

}
