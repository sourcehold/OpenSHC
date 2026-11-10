#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D720
void Meta::Destructor_0059d720()
{
    ((void(__fastcall*)(BuildingsState*))MACRO_CALL(Global_Func::DoNothing))(DAT_BuildingsState::ptr);
}

}
