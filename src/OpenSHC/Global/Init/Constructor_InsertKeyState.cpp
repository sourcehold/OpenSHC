#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Input/InsertKeyState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_InsertKeyState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C7C0
    void Init::Constructor_InsertKeyState()
    {
        MACRO_CALL_MEMBER(Input::InsertKeyState_Func::Constructor_InsertKeyState, DAT_InsertKeyState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_InsertKeyState::get());
    }

}
}
