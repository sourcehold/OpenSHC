#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C760
    void Init::Constructor_MouseState()
    {
        MACRO_CALL_MEMBER(Input::MouseState_Func::Constructor_MouseState, DAT_MouseState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d500::get());
    }

}
}
