#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A94E0
        void PathFindingState::clearAllClimbData()
        {
            this->numberOfClimbTeleports = 0;
            for (int _climbDataID = 0; _climbDataID < 200; ++_climbDataID) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(_climbDataID);
            }
        }

    }
}
}
