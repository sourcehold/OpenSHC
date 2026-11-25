#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00405CF0
        void EntityState::setProjectileTargetPosition(
            int entityID, int x, int y, int height, int targetX, int targetY, int targetZ)
        {
            this->entityArray[entityID].microX = x;
            this->entityArray[entityID].x_2 = x;
            this->entityArray[entityID].microY = y;
            this->entityArray[entityID].y_2 = y;
            this->entityArray[entityID].height = height;
            this->entityArray[entityID].startingHeight_2 = height;
            this->entityArray[entityID].height_2 = height;
            this->entityArray[entityID].startingHeight = height;
            this->entityArray[entityID].targetX = targetX;
            this->entityArray[entityID].targetY = targetY;
            this->entityArray[entityID].targetZ = targetZ;
            this->entityArray[entityID].heightDifference = targetZ - height;
            MACRO_CALL_MEMBER(Navigation::DirectionAlgorithmState_Func::somethingWithProjectileDistance,
                DAT_DirectionAlgorithmState::ptr)(x, y, targetX, targetY);
            this->entityArray[entityID].orientation = DAT_DirectionAlgorithmState::instance.orientation;
            MACRO_CALL_MEMBER(EntityState_Func::initializeProjectileVelocities, this)(
                entityID, x, y, height, targetX, targetY, targetZ);
        }

    }
}
}
