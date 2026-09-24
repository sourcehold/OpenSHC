#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LandscapeState;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3930
    LandscapeState* LandscapeState::constructLandscapeState()
    {
        this->creationTime = timeGetTime();
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::clearRocksAndTrees, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::resetWind, this)();
        this->field1_0x4 = 1;
        return this;
    }

}
}
