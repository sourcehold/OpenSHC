#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CCB0
    void Init::Constructor_MapPropertiesState()
    {
        ((void*(__fastcall*)(MapPropertiesState*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(
            DAT_MapPropertiesState::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d7b0::get());
    }

}
}
