#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // The random value is the signed short currentNumber2 (orig movsx 0x405C35); all three remainders are signed
    // (cdq; idiv at 0x405C45 / 0x405C5C / 0x405C78), the second one of (value >> 8) with an arithmetic shift.
    // FUNCTION: STRONGHOLDCRUSADER 0x00405C00
    void Entities::UpdateHeadsOnSpikesEntity()
    {
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 + 1;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2--;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2 == 0) {
            short randomValue = SEC_RNG::instance.currentNumber2;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2
                = randomValue % 500 + 300;
            int targetTileX = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition
                + randomValue % 100 - 0x32;
            int targetTileY = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition
                + (randomValue >> 8) % 100 - 0x32;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(0,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner, 0,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height + 0x32, targetTileX * 8,
                targetTileY * 8, 0xfa, OpenSHC::Map::Entities::EntityTypeInt__ET_CROW, 0);
        }
    }

}
}
