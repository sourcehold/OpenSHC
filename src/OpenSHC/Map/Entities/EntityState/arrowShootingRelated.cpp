#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00404A10
        int EntityState::arrowShootingRelated(
            int microX, int microY, int height, int destMicroX, int destMicroY, int destHeight)
        {
            uint uVar1;
            uVar1 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                microX, microY, height, destMicroX, destMicroY, destHeight, 0);
            if (!uVar1) {
                uVar1 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                    destMicroX, destMicroY, destHeight, microX, microY, height, 0);
            }
            return (int)(uVar1);
        }

    }
}
}
