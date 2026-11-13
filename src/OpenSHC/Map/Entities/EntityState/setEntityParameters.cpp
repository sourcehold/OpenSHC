#include "OpenSHC/Map/Entities/EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004012F0
        void EntityState::setEntityParameters(int entityID, undefined4 entityType, int gmLookupValue)
        {
            this->entityArray[entityID].entityType = (EntityTypeShort)entityType;
            this->entityArray[entityID].gmLookupValue = (short)gmLookupValue;
            this->entityArray[entityID].gmID = (short)DAT_EntityDefinedData::instance.EntityGmIDs[gmLookupValue];
            this->entityArray[entityID].graphicType2RelatedOffset
                = (short)DAT_EntityDefinedData::instance.EntityGraphicOffsets[gmLookupValue];
            this->entityArray[entityID].originX = (short)DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originX;
            this->entityArray[entityID].originY = (short)DAT_TextureRenderCoreObject::instance
                                                      .gmFileHeaderColorpaletteArray[this->entityArray[entityID].gmID]
                                                      .originY;
            this->entityArray[entityID].unkOne_1 = (short)DAT_EntityDefinedData::instance.field_0x8a4[gmLookupValue];
            this->entityArray[entityID].unkThree_1 = (short)DAT_EntityDefinedData::instance.field_0x7ec[gmLookupValue];
            if (gmLookupValue == 1) {
                this->entityArray[entityID].unkThree_1 = 5;
                this->entityArray[entityID].unkOne_1 = 3;
                this->entityArray[entityID].unkMinusOne = 16;
            }
        }

    }
}
}
