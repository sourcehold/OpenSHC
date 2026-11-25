#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CCD0
    void Init::Constructor_GameSynchronyState()
    {
        MACRO_CALL_MEMBER(
            Synchrony::GameSynchronyState_Func::Constructor_GameSynchronyState, DAT_GameSynchronyState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d7c0::get());
    }

}
}
