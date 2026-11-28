#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004081E0
        void EntityState::updateProjectileHeightAndCollision(
            uint entityID, undefined4 param_2, int param_3, int param_4)
        {
            short sVar1;
            undefined4 uVar2;
            sVar1 = this->entityArray[entityID].startingHeight + (short)param_2;
            this->entityArray[entityID].height = sVar1;
            if ((sVar1 < 3) && (!param_4)) {
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::doSomethingWithOtherEntitiesOnTile, this)(
                    entityID);
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit, this)(
                    entityID);
            }
            sVar1 = this->entityArray[entityID].height;
            if (10000 < sVar1) {
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::markEntityDestroyed, this)(entityID);
            }
            uVar2
                = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::angleToRotationFrameIndex, this)(param_3);
            this->entityArray[entityID].rotationFrameIndex = (short)uVar2;
            this->entityArray[entityID].height_2 = sVar1;
        }

    }
}
}
