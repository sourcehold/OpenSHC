#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401A50
        BOOLEnum EntityState::isBrazierNearby(int unitX, int unitY, int unitZ)
        {
            for (int entityID = 1; entityID < (int)this->maxEntityCount; entityID++) {
                if (this->entityArray[entityID].logicalState == 2
                    && this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_BRAZIER) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(unitX, unitY, this->entityArray[entityID].xPosition,
                        this->entityArray[entityID].yPosition);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh <= 3
                        && abs(unitZ - this->entityArray[entityID].height) < 45) {
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
