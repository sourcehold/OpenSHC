#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D500
void Meta::Destructor_0059d500()
{
    ((void(__fastcall*)(MouseState*))MACRO_CALL(Global_Func::DoNothing))(DAT_MouseState::ptr);
}

}
