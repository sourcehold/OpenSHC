#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C880
    void Init::Constructor_LowLevelMemory()
    {
        ((void*(__fastcall*)(LowLevelMemory*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(
            DAT_LowLevelMemory::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d590::get());
    }

}
}
