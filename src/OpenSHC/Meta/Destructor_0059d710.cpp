#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D710
void Meta::Destructor_0059d710()
{
    ((void(__fastcall*)(TroopValueState*))MACRO_CALL(Global_Func::DoNothing))(DAT_TroopValueState::ptr);
}

}
