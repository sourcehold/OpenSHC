#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C900
    void Init::Constructor_DirectionAlgorithmState()
    {
        ((void*(__fastcall*)(DirectionAlgorithmState*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(
            DAT_DirectionAlgorithmState::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d5d0::get());
    }

}
}
