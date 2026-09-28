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
            int iVar1;
            int* piVar2;
            iVar1 = 1;
            piVar2 = &this->climbData[1].type;
            do {
                if (((ClimbData*)(piVar2 + -1))->canBeUsed != 0) {
                    if (*piVar2 == 6) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(iVar1);
                    }
                    if (*piVar2 == 7) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(iVar1);
                    }
                }
                iVar1 = iVar1 + 1;
                piVar2 = piVar2 + 0x81;
            } while (iVar1 < 200);
            return;
        }

    }
}
}
