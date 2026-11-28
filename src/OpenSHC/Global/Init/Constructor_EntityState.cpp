#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CB40
    void Init::Constructor_EntityState()
    {
        MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::Constructor_EntityState, DAT_EntityState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_0059d6f0));
        return;
    }

}
}
