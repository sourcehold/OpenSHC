#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401D70
    void Entities::UpdateArrowsSecondaryEntity()
    {
        short animFrame = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        short frameCount = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkThree_1;
        if (animFrame >= frameCount) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            return;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = (animFrame * 32) / frameCount;
    }

}
}
