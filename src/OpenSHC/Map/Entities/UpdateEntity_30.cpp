#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004024F0
    void Entities::UpdateEntity_30()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID != 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID++;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround = 1;
            return;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround = 0;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated >= 8) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 7;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated + 1;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated + 9;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = -1;
    }

}
}
