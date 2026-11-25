#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C9F0
    void Init::Constructor_AlphaAndButtonSurface()
    {
        MACRO_CALL_MEMBER(UI::Rendering::AlphaAndButtonSurface_Func::Constructor_AlphaAndButtonSurface,
            AlphaAndButtonSurfaceObj::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_AlphaAndButtonSurface::get());
    }

}
}
