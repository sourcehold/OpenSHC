#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C720
    void Init::Constructor_WindowAndDirectDraw()
    {
        MACRO_CALL_MEMBER(
            UI::Rendering::WindowAndDirectDraw_Func::Constructor_WindowAndDirectDraw, DAT_WindowAndDirectDraw::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d4e0::get());
    }

}
}
