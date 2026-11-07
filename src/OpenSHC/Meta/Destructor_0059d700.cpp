#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D700
void Meta::Destructor_0059d700()
{
    ((void(__fastcall*)(TribesState*))MACRO_CALL(Global_Func::DoNothing))(DAT_TribesState::ptr);
}

}
