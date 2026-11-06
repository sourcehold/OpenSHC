#include "../Meta.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D4E0
void Meta::Destructor_0059d4e0()
{
    MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::cleanDirectDraw, DAT_WindowAndDirectDraw::ptr)();
}

}
