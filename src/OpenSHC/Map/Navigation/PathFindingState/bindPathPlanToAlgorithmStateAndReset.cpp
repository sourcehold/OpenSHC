#include "../PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00496EA0
        void PathFindingState::bindPathPlanToAlgorithmStateAndReset(byte* pPathPlan)
        {
            this->searchQueue.ptrPathPlan = pPathPlan;
            this->searchQueue.pathPlanIndex = 0;
            return;
        }

    }
}
}
