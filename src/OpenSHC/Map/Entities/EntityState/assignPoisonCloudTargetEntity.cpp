#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401910
        void EntityState::assignPoisonCloudTargetEntity(int param_1)
        {
            for (int i = 1; i < this->maxEntityCount; ++i) {
                if (this->entityArray[i].logicalState == 2
                    && this->entityArray[i].entityType == OpenSHC::Map::Entities::ET_COW_POISON_CLOUD
                    && this->entityArray[i].unknownAnimationFrameRelated <= 1000
                    && this->entityArray[i].unitID_healer == 0
                    && this->entityArray[i].unknownDistanceRelatedValue == 0) {
                    MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(this->entityArray[i].xPosition,
                        this->entityArray[i].yPosition, this->entityArray[param_1].xPosition,
                        this->entityArray[param_1].yPosition);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < 7) {
                        this->entityArray[i].unknownDistanceRelatedValue = param_1;
                        this->entityArray[i].uidRef = DAT_EntityState::instance.entityArray[param_1].uid;
                    }
                }
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
