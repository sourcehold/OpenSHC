#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401EA0
    void Entities::UpdateEntity_21()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID != 2) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated * 15 / 400 + 0x10;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated < 400) {
                if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated < 8) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                        = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
                        - DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated + 7;
                    return;
                }
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                    = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated * 15 / 400
                    + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
                return;
            }
        }
        else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated * 7 / 200 + 0x18;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated >= 200) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
                return;
            }
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated < 12) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                    = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
                    - DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated / 4 + 15;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                    = 0x1f - DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated / 4;
                return;
            }
            int frame = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated * 16 / 200;
            if (frame >= 4) {
                frame = 4;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset + 11
                + frame;
            return;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
    }

}
}
