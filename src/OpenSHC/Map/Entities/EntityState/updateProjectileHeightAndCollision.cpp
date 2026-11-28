#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004081E0
        void EntityState::updateProjectileHeightAndCollision(
            uint entityID, undefined4 param_2, int param_3, int param_4)
        {
            this->entityArray[entityID].height = this->entityArray[entityID].startingHeight + (short)param_2;
            if (this->entityArray[entityID].height <= 2 && !param_4) {
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(entityID);
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit, this)(entityID);
            }
            short const currentHeight = this->entityArray[entityID].height;
            if (currentHeight > 10000) {
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::markEntityDestroyed, this)(entityID);
                return;
            }
            this->entityArray[entityID].rotationFrameIndex
                = (short)MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::angleToRotationFrameIndex, this)(param_3);
            this->entityArray[entityID].height_2 = currentHeight;
        }

    }
}
}
