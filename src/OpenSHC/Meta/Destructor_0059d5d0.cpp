#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D5D0
void Meta::Destructor_0059d5d0()
{
    ((void(__fastcall*)(DirectionAlgorithmState*))MACRO_CALL(Global_Func::DoNothing))(DAT_DirectionAlgorithmState::ptr);
}

}
