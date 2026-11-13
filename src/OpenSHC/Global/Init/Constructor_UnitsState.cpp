#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CB20
    void Init::Constructor_UnitsState()
    {
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::Constructor_UnitsState, DAT_UnitsState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d6e0::get());
    }

}
}
