#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x00496EA0
        void PathFindingState::bindPathPlanToAlgorithmStateAndReset(byte* pPathPlan)
        {
            this->searchQueue.ptrPathPlan = pPathPlan;
            this->searchQueue.pathPlanIndex = 0;
        }

    }
}
}
