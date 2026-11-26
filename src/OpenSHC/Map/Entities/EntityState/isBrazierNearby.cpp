#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401A50
        BOOLEnum EntityState::isBrazierNearby(int unitX, int unitY, int unitZ)
        {
            for (int i = 1; i < this->maxEntityCount; ++i) {
                if (this->entityArray[i].logicalState == 2
                    && this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_BRAZIER) {
                    MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(
                        unitX, unitY, this->entityArray[i].xPosition, this->entityArray[i].yPosition);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh <= 3
                        && abs(unitZ - this->entityArray[i].height) < 45) {
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
