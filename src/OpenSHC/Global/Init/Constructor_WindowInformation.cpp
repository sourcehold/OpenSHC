#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_WindowInformation.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C740
    void Init::Constructor_WindowInformation()
    {
        ((void*(__fastcall*)(WindowInformation*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(
            DAT_WindowInformation::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d4f0::get());
    }

}
}
