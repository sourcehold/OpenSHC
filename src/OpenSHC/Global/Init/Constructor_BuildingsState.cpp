#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CBA0
    void Init::Constructor_BuildingsState()
    {
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::Constructor_BuildingsState, DAT_BuildingsState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d720::get());
    }

}
}
