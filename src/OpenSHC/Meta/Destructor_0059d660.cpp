#include "../Meta.func.hpp"

#include "OpenSHC/Global.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D660
void Meta::Destructor_0059d660()
{
    ((void(__fastcall*)(ViewportRenderState*))MACRO_CALL(Global_Func::DoNothing))(DAT_ViewportRenderState::ptr);
}

}
