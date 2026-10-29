#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00405B70
    void Entities::UpdateFirethrowEntity()
    {
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround != 0) {
            MACRO_CALL(OpenSHC::Map::Entities_Func::AFireSpreadFunction)(
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY,
                DAT_TileMapState::instance
                    .HeightLayer[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile],
                2, 1);
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
        }
    }

}
}
