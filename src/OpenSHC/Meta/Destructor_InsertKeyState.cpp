#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_InsertKeyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D530
void Meta::Destructor_InsertKeyState()
{
    ((void(__fastcall*)(InsertKeyState*))MACRO_CALL(Global_Func::DoNothing))(DAT_InsertKeyState::ptr);
}

}
