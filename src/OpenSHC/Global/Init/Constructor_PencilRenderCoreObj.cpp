#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C7E0
    void Init::Constructor_PencilRenderCoreObj()
    {
        ((void*(__fastcall*)(PencilRenderCore*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(
            DAT_PencilRenderCore::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d540::get());
    }

}
}
