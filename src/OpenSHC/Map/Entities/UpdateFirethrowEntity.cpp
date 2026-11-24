#include "../../Map.func.hpp"

#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00405B70
    void Entities::UpdateFirethrowEntity()
    {
        uint uVar1;
        uVar1 = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        if (DAT_EntityState::instance.entityArray[uVar1].someCounter_OR_hitGround != 0) {
            MACRO_CALL(Map::Entities_Func::AFireSpreadFunction)(
                (int)DAT_EntityState::instance.entityArray[uVar1].owner,
                (int)((int)(DAT_EntityState::instance.entityArray[uVar1].microX)),
                (int)((int)(DAT_EntityState::instance.entityArray[uVar1].microY)),
                (int)((int)((
                    uint)DAT_TileMapState::instance.HeightLayer[DAT_EntityState::instance.entityArray[uVar1].tile])),
                2, 1);
            uVar1 = DAT_CurrentEntityID::instance;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
        }
        if (DAT_EntityState::instance.entityArray[uVar1].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[uVar1].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[uVar1].logicalState = 7;
        }
    }

}
}
