#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401DB0
    void Entities::UpdateCrossbowArrowEntity()
    {
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rotationFrameIndex * 16
            + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
            + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirection;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround != 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround -= 1;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround <= 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
            }
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation == 76) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation = 60;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
        }
    }

}
}
