#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // The return value is not meaningful (the callers ignore it); it reproduces what the original leaves in eax.
    // FUNCTION: STRONGHOLDCRUSADER 0x004023F0
    uint Entities::UpdateEntity_29()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].targetZ == 0) {
            uint result = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirection + 0x91;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = result;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirection + 0xa1;
            return result;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2 < 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 3;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated >= 8) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated + 1
            + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirection * 8;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirection + 0x81;
        short randomValue = SEC_RNG::instance.currentNumber2;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2 > 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2--;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2 == 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2
                    = -10 - randomValue % 50;
            }
        }
        uint result = (ushort)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2;
        if ((short)result < 0) {
            result++;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2 = (short)result;
            if ((short)result == 0) {
                result = randomValue / 200;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2
                    = randomValue % 200 + 0xaa;
            }
        }
        return result;
    }

}
}
