#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D550
void Meta::Destructor_0059d550()
{
    ((void(__fastcall*)(UserTextHandler*))MACRO_CALL(Global_Func::DoNothing))(DAT_UserTextHandlerState::ptr);
}

}
