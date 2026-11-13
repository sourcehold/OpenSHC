#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CBC0
    void Init::Constructor_AIVState()
    {
        MACRO_CALL_MEMBER(AI::AIVState_Func::Constructor_AIVState, DAT_AIVState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d730::get());
    }

}
}
