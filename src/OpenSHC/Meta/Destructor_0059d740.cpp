#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D740
void Meta::Destructor_0059d740()
{
    ((void(__fastcall*)(AICState*))MACRO_CALL(Global_Func::DoNothing))(DAT_AICState::ptr);
}

}
