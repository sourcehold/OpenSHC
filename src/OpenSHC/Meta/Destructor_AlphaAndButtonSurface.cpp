#include "../Meta.func.hpp"

#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D640
void Meta::Destructor_AlphaAndButtonSurface()
{
    MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::freeMemory, AlphaAndButtonSurfaceObj::ptr)();
}

}
