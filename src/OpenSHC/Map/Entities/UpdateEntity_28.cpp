#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004023A0
    void Entities::UpdateEntity_28()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated >= 12) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated + 1
            + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirection * 12;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
            = (short)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2;
    }

}
}
