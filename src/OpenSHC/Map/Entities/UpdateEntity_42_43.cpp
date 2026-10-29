#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_GmRunCopyJumpTable.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402820
    void Entities::UpdateEntity_42_43()
    {
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkOne_1 = 2;
        int animTick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (DAT_EntityDefinedData::instance.SharedEntityAnimationFrames[animTick] <= 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
        }
        else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                = (short)DAT_EntityDefinedData::instance.SharedEntityAnimationFrames[animTick] - 1;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 1;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field82_0xbe = 0x2e;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field86_0xc8 = 0x16;
        short tick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (tick > 0x10) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field86_0xc8 = 0x26 - tick;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field87_0xca = 0x2d
            - *(short*)((int)PTR_ARRAY_GmRunCopyJumpTable::instance
                  + (GMFirstPictureIndex::instance[DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                                                       .field82_0xbe]
                        + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field83_0xc0)
                      * 0x10
                  + 0x72)
                / 2;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field88_0xcc = 0x32;
        tick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (tick > 0x10) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field88_0xcc = tick + 0x22;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field89_0xce = 0x27;
    }

}
}
