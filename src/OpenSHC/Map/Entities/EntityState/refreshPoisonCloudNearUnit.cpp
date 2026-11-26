#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401880
        void EntityState::refreshPoisonCloudNearUnit(int param_1)
        {
            for (int i = 1; i < this->maxEntityCount; ++i) {
                if (this->entityArray[i].logicalState == 2
                    && this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_COW_POISON_CLOUD
                    && this->entityArray[i].unknownAnimationFrameRelated <= 1000) {
                    MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[param_1].x,
                        DAT_UnitsState::instance.units[param_1].y, this->entityArray[i].xPosition,
                        this->entityArray[i].yPosition);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < 7) {
                        this->entityArray[i].unknownAnimationFrameRelated = 1016;
                    }
                }
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
