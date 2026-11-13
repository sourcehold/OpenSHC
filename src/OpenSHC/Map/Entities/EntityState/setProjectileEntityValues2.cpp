#include "OpenSHC/Map/Entities/EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004011D0
        void EntityState::setProjectileEntityValues2(int entityID, EntityType entityType)
        {
            this->entityArray[entityID].entityType = (EntityTypeShort)entityType;
            this->entityArray[entityID].gmID = (short)DAT_EntityDefinedData::instance.EntityPropertyArray_1[entityType];
            this->entityArray[entityID].graphicType2RelatedOffset
                = (short)DAT_EntityDefinedData::instance.EntityPropertyArray_2[entityType];
            this->entityArray[entityID].originX = (short)DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originX;
            this->entityArray[entityID].originY = (short)DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originY;
            this->entityArray[entityID].unkOne_1
                = (short)DAT_EntityDefinedData::instance.EntityPropertyArray_3[entityType];
            int const curveType = DAT_EntityDefinedData::instance.EntityArrayCurveTypeForProjectileType[entityType];
            if (curveType != 0 && curveType != 6 && curveType != 9) {
                this->entityArray[entityID].startingAngle
                    = (short)DAT_EntityDefinedData::instance.EntityArrayProjectileVelocityForProjectileType[entityType];
            } else {
                this->entityArray[entityID].velocityUnk
                    = (short)DAT_EntityDefinedData::instance.EntityArrayProjectileVelocityForProjectileType[entityType];
            }
            this->entityArray[entityID]._elapsedTimeOrGravityAccumulator
                = DAT_EntityDefinedData::instance.ProjectileGravityPerEntityType[entityType];
            this->entityArray[entityID].field_0x5a
                = (short)DAT_EntityDefinedData::instance.field_0x2ac[entityType - 10];
            this->entityArray[entityID].gmLookupValue
                = (short)DAT_EntityDefinedData::instance.field_0x75c[entityType - 10];
            switch (entityType) {
            case 11:
                this->entityArray[entityID].originX += -1;
                this->entityArray[entityID].originY += -2;
                break;
            case 12:
                this->entityArray[entityID].originX += 8;
                this->entityArray[entityID].originY += -8;
                break;
            case 13:
                this->entityArray[entityID].originX += 8;
                this->entityArray[entityID].originY += -7;
                break;
            case 10:
            case 14:
            case 15:
                this->entityArray[entityID].originX += -1;
                this->entityArray[entityID].originY += -7;
                break;
            }
        }

    }
}
}
