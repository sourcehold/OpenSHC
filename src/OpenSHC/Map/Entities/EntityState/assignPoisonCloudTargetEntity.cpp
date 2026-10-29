#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401910
        void EntityState::assignPoisonCloudTargetEntity(int claimedCloudID)
        {
            for (int cloudEntityID = 1; cloudEntityID < (int)this->maxEntityCount; cloudEntityID++) {
                if (this->entityArray[cloudEntityID].logicalState == 2
                    && this->entityArray[cloudEntityID].entityType == OpenSHC::Map::Entities::ET_COW_POISON_CLOUD
                    && this->entityArray[cloudEntityID].unknownAnimationFrameRelated <= 1000
                    && this->entityArray[cloudEntityID].unitID_healer == 0
                    && this->entityArray[cloudEntityID].unknownDistanceRelatedValue == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(this->entityArray[cloudEntityID].xPosition,
                        this->entityArray[cloudEntityID].yPosition, this->entityArray[claimedCloudID].xPosition,
                        this->entityArray[claimedCloudID].yPosition);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < 7) {
                        this->entityArray[cloudEntityID].unknownDistanceRelatedValue = claimedCloudID;
                        this->entityArray[cloudEntityID].uidRef
                            = DAT_EntityState::instance.entityArray[claimedCloudID].uid;
                    }
                }
            }
        }

    }
}
}
