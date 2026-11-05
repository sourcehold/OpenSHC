#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D650
void Meta::Destructor_0059d650()
{
    ((void(__fastcall*)(MenuHandlerState*))MACRO_CALL(Global_Func::DoNothing))(DAT_MenuHandlerState::ptr);
}

}
