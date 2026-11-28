#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CB80
    void Init::Constructor_TroopValueState()
    {
        MACRO_CALL_MEMBER(
            Map::Units::TroopValueState_Func::Constructor_TroopValueState, DAT_TroopValueState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_0059d710));
        return;
    }

}
}
