#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Input/ModifierKeyState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C780
    void Init::Constructor_ModifierKeyState()
    {
        MACRO_CALL_MEMBER(Input::ModifierKeyState_Func::Constructor_ModifierKeyState, DAT_ModifierKeyState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d510::get());
    }

}
}
