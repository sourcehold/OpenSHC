#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D6F0
void Meta::Destructor_0059d6f0()
{
    ((void(__fastcall*)(EntityState*))MACRO_CALL(Global_Func::DoNothing))(DAT_EntityState::ptr);
}

}
