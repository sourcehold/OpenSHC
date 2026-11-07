#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/UNK_UnusedClass1Location.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C840
    void Init::Constructor_UnusedClass1Unk()
    {
        ((void*(__fastcall*)(void*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(UNK_UnusedClass1Location::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d570::get());
    }

}
}
