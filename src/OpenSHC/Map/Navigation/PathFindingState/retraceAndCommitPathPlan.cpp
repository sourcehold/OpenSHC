#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Navigation {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004A9DD0
undefined4 PathFindingState::retraceAndCommitPathPlan()

{
this->searchQueue.pathPlanIndex = 0;
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::traceAndCommitPathPlan, this)(this->unitX, (uint)((int)(this->unitY)), (uint)((int)(
this->destinationX)), (uint)((int)(this->destinationY)), 0);
return this->searchQueue.pathPlanIndex;
}


}
}
}