#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00404A10
        int EntityState::arrowShootingRelated(
            int microX, int microY, int height, int destMicroX, int destMicroY, int destHeight)
        {
            uint distance = MACRO_CALL_MEMBER(EntityState_Func::computeLineOfSightDistance, this)(
                microX, microY, height, destMicroX, destMicroY, destHeight, 0);
            if (distance == 0) {
                distance = MACRO_CALL_MEMBER(EntityState_Func::computeLineOfSightDistance, this)(
                    destMicroX, destMicroY, destHeight, microX, microY, height, 0);
            }
            return distance;
        }

    }
}
}
