#include "OpenSHC/Map/Entities/EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401380
        void EntityState::drawEntityEffect(int entityID, undefined4 entityType, int graphicType1, int graphicType2)
        {
            this->entityArray[entityID].entityType = (EntityTypeShort)entityType;
            this->entityArray[entityID].graphicType2 = graphicType2;
            this->entityArray[entityID].gmID = (short)graphicType1;
            this->entityArray[entityID].originX
                = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[(short)graphicType1]
                      .originX;
            this->entityArray[entityID].originY
                = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[(short)graphicType1]
                      .originY;
            this->entityArray[entityID].unkOne_1 = (short)DAT_EntityDefinedData::instance.field_0x8b0;
            this->entityArray[entityID].unkThree_1 = (short)DAT_EntityDefinedData::instance.field_0x7f8;
            if (graphicType1 == 135) {
                this->entityArray[entityID].unkOne_1 = 1;
                this->entityArray[entityID].unkThree_1 = 3;
            }
        }

    }
}
}
