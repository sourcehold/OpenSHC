#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/IO/BitMapState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_BitMapState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C8E0
    void Init::Constructor_BitMapState()
    {
        MACRO_CALL_MEMBER(IO::BitMapState_Func::Constructor_BitMapState, DAT_BitMapState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d5c0::get());
    }

}
}
