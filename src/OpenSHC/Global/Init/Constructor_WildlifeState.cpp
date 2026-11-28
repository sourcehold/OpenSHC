#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CAE0
    void Init::Constructor_WildlifeState()
    {
        MACRO_CALL_MEMBER(Map::WildlifeState_Func::Constructor_WildlifeState, DAT_WildlifeState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_0059d6c0));
        return;
    }

}
}
