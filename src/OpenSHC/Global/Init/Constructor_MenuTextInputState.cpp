#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CC40
    void Init::Constructor_MenuTextInputState()
    {
        MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::Constructor_MenuTextInputState, DAT_MenuTextInputState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d770::get());
    }

}
}
