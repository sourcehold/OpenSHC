#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C820
    void Init::Constructor_TextManagerObj()
    {
        ((void*(__fastcall*)(TextManager*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(
            DAT_TextManagerObject::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d560::get());
    }

}
}
