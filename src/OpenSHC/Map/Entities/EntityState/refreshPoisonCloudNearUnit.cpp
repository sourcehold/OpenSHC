#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401880
        void EntityState::refreshPoisonCloudNearUnit(int unitID)
        {
            for (int entityID = 1; entityID < (int)this->maxEntityCount; entityID++) {
                if (this->entityArray[entityID].logicalState == 2
                    && this->entityArray[entityID].entityType == OpenSHC::Map::Entities::ET_COW_POISON_CLOUD
                    && this->entityArray[entityID].unknownAnimationFrameRelated <= 1000) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                        DAT_UnitsState::instance.units[unitID].y, this->entityArray[entityID].xPosition,
                        this->entityArray[entityID].yPosition);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < 7) {
                        this->entityArray[entityID].unknownAnimationFrameRelated = 1016;
                    }
                }
            }
        }

    }
}
}
