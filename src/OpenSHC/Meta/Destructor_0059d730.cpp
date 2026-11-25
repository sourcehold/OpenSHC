#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D730
void Meta::Destructor_0059d730()
{
    ((void(__fastcall*)(AIVState*))MACRO_CALL(Global_Func::DoNothing))(DAT_AIVState::ptr);
}

}
