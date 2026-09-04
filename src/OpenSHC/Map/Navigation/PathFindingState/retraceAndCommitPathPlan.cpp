#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A9DD0
        undefined4 PathFindingState::retraceAndCommitPathPlan()
        {
            this->searchQueue.pathPlanIndex = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::traceAndCommitPathPlan, this)(
                this->unitX, this->unitY, this->destinationX, this->destinationY, 0);
            return this->searchQueue.pathPlanIndex;
        }

    }
}
}
