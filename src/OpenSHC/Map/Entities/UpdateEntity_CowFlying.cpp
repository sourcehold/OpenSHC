#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402180
    void Entities::UpdateEntity_CowFlying()
    {
        uint const entityID = DAT_CurrentEntityID::instance;
        if (DAT_EntityState::instance.entityArray[entityID].someCounter_OR_hitGround != 0) {
            if (DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated < 100) {
                DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated = 100;
            }
            if (DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated >= 120) {
                DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated = 119;
            }
            short* const counter = &DAT_EntityState::instance.entityArray[entityID].someCounter_OR_hitGround;
            *counter = *counter - 1;
            if (*counter <= 0) {
                DAT_EntityState::instance.entityArray[entityID].logicalState = 7;
            }
            DAT_EntityState::instance.entityArray[entityID].graphicType2
                = (DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated - 100) / 4 + 0xc
                + DAT_EntityState::instance.entityArray[entityID].graphicType2RelatedOffset;
            DAT_EntityState::instance.entityArray[entityID].imageID = 0;
        } else {
            if (DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated >= 12) {
                DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated = 0;
            }
            DAT_EntityState::instance.entityArray[entityID].graphicType2
                = DAT_EntityState::instance.entityArray[entityID].graphicType2RelatedOffset
                + DAT_EntityState::instance.entityArray[entityID].unknownAnimationFrameRelated;
            DAT_EntityState::instance.entityArray[entityID].imageID
                = (short)(DAT_EntityState::instance.entityArray[entityID].graphicType2 + 0x11);
        }
        if (DAT_EntityState::instance.entityArray[entityID].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[entityID].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[entityID].logicalState = 7;
        }
    }

}
}
