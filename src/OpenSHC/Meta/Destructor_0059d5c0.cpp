#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_BitMapState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D5C0
void Meta::Destructor_0059d5c0()
{
    ((void(__fastcall*)(BitMapState*))MACRO_CALL(Global_Func::DoNothing))(DAT_BitMapState::ptr);
}

}
