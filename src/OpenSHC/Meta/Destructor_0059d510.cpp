#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D510
void Meta::Destructor_0059d510()
{
    ((void(__fastcall*)(ModifierKeyState*))MACRO_CALL(Global_Func::DoNothing))(DAT_ModifierKeyState::ptr);
}

}
