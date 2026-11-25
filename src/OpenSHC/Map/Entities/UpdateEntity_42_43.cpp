#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402820
    void Entities::UpdateEntity_42_43()
    {
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkOne_1 = 2;
        int animTick
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (DAT_EntityDefinedData::instance.SharedEntityAnimationFrames[animTick] <= 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
        } else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                = (short)DAT_EntityDefinedData::instance.SharedEntityAnimationFrames[animTick] - 1;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 1;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xbe = 46;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xc8 = 22;
        short tick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (tick > 16) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xc8 = 38 - tick;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xca = 45
            - *(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                  + (GMFirstPictureIndex::instance[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                             .field_0xbe]
                        + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xc0)
                      * 0x10
                  + 114)
                / 2;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xcc = 50;
        tick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (tick > 16) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xcc = tick + 34;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field_0xce = 39;
    }

}
}
