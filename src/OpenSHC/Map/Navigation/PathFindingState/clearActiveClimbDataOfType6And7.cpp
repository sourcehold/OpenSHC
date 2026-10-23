#include "../PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A52D0
        void PathFindingState::clearActiveClimbDataOfType6And7()
        {
            for (int climbID = 1; climbID < 200; ++climbID) {
                if (this->climbData[climbID].canBeUsed != 0) {
                    if (this->climbData[climbID].type == 6) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(
                            climbID);
                    }
                    if (this->climbData[climbID].type == 7) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(
                            climbID);
                    }
                }
            }
        }

    }
}
}
