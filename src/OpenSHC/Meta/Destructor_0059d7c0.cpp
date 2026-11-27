#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7C0
void Meta::Destructor_0059d7c0()
{
    ((void(__fastcall*)(GameSynchronyState*))MACRO_CALL(Global_Func::DoNothing))(DAT_GameSynchronyState::ptr);
}

}
