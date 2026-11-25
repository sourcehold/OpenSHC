#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7B0
void Meta::Destructor_0059d7b0()
{
    ((void(__fastcall*)(MapPropertiesState*))MACRO_CALL(Global_Func::DoNothing))(DAT_MapPropertiesState::ptr);
}

}
