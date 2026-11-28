#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CAC0
    void Init::Constructor_TileMapState()
    {
        MACRO_CALL_MEMBER(Map::TileMapState_Func::Constructor_TileMapState, DAT_TileMapState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_0059d6b0));
        return;
    }

}
}
