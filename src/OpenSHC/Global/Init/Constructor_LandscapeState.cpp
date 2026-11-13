#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CC00
    void Init::Constructor_LandscapeState()
    {
        MACRO_CALL_MEMBER(Map::LandscapeState_Func::Construct_LandscapeState, DAT_LandscapeState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d750::get());
    }

}
}
