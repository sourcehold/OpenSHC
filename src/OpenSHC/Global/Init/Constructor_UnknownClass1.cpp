#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/UNK_UnknownClassLocation2.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C700
    void Init::Constructor_UnknownClass1()
    {
        ((void*(__fastcall*)(void*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(UNK_UnknownClassLocation2::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d4d0::get());
    }

}
}
