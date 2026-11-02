#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402660
    void Entities::UpdateEntity_40()
    {
        int ownerID = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkOne_1 = 2;
        int animTick
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (DAT_EntityDefinedData::instance.SharedEntityAnimationFrames[animTick] <= 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            DAT_GameState::instance.playerDataArray[ownerID].someCount32 = 70;
        } else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                = (short)DAT_EntityDefinedData::instance.SharedEntityAnimationFrames[animTick] - 1;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 1;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field82_0xbe = 46;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field83_0xc0 = 171;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field86_0xc8 = 22;
        short tick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (tick > 16) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field86_0xc8 = 38 - tick;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field87_0xca = 40;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field88_0xcc = 50;
        tick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (tick > 16) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field88_0xcc = tick + 34;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field89_0xce = 39;
    }

}
}
