#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402A20
    void Entities::UpdateFlag3Entity()
    {
        int frameOffset;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        if ((int)((byte)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition & 0x1f)
            >= DAT_LandscapeState::instance.wind.countdown) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2
                = (short)DAT_LandscapeState::instance.wind.value;
        }
        switch (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker) {
        case 0:
            frameOffset = DAT_EntityDefinedData::instance
                              .Flag3AnimationFrames1[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                                         .unknownAnimationFrameRelated];
            if (frameOffset <= 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker
                    = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2;
                return;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 += frameOffset - 1;
            return;
        case 1:
        case 2:
            frameOffset
                = DAT_EntityDefinedData::instance
                      .Flag3AnimationFrames2[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                                  .unknownAnimationFrameRelated];
            if (frameOffset <= 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someTracker
                    = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2;
                return;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 += frameOffset - 1;
            return;
        }
    }

}
}
