#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C800
    void Init::Constructor_UserTextHandler()
    {
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::FUN_004694a0, DAT_UserTextHandlerState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_0059d550));
        return;
    }

}
}
