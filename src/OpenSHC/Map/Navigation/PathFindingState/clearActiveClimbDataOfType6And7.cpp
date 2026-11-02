#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          Iterates all climb data entries (1 to maxClimbDataCount) and calls clearLaddermanWalledData on   any entry
          that is active (canBeUsed != 0) and has type 6 or 7. The semantics of types 6 and 7 are   not yet fully known;
          this is likely called during a siege reset or wall state change.      renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A52D0
        void PathFindingState::clearActiveClimbDataOfType6And7()
        {
            for (int _climbDataID = 1; _climbDataID < 200; ++_climbDataID) {
                if (this->climbData[_climbDataID].canBeUsed == 0) {
                    continue;
                }
                if (this->climbData[_climbDataID].type == 6) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(
                        _climbDataID);
                }
                if (this->climbData[_climbDataID].type == 7) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(
                        _climbDataID);
                }
            }
        }

    }
}
}
