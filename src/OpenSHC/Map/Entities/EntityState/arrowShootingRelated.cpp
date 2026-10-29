#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00404A10
        int EntityState::arrowShootingRelated(
            int microX, int microY, int high, int destMicroX, int destMicroY, int destHeight)
        {
            int distance = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeLineOfSightDistance,
                this)(microX, microY, high, destMicroX, destMicroY, destHeight, 0);
            if (distance == 0) {
                distance = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeLineOfSightDistance,
                    this)(destMicroX, destMicroY, destHeight, microX, microY, high, 0);
            }
            return distance;
        }

    }
}
}
