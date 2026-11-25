#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CBE0
    void Init::Constructor_AICState()
    {
        MACRO_CALL_MEMBER(AI::AICState_Func::Constructor_AICState, DAT_AICState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d740::get());
    }

}
}
