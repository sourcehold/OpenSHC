#include "../../Map.func.hpp"

#include "OpenSHC/Map/WildlifeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0052DF10
    WildlifeState* WildlifeState::Constructor_WildlifeState()
    {
        MACRO_CALL_MEMBER(Map::WildlifeState_Func::clearWildlifeState, this)();
        this->DAT_DebugDataMapDataDisplayType = 8;
        return this;
    }

}
}
