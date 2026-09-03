#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A94E0
        void PathFindingState::clearAllClimbData()
        {
            this->numberOfClimbTeleports = 0;
            for (int iVar1 = 0; iVar1 < 200; iVar1++) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(iVar1);
            }
        }

    }
}
}
