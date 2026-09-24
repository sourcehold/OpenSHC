#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00410800
        void BuildingsState::spawnRandomFireEffectOnBuilding(int buildingID, undefined4 playerID)
        {
            if (this->buildings[buildingID].fireDuration < 400) {
                return;
            }

            // Smaller buildings spawn fire effects more often
            int tick;
            int interval;
            if ((int)this->buildings[buildingID].widthOrHeight < 4) {
                interval = 24 - this->buildings[buildingID].widthOrHeight * 5;
                tick = this->buildings[buildingID].fireRelatedRNG1 + this->buildings[buildingID].fireDuration;
            } else {
                tick = this->buildings[buildingID].fireRelatedRNG1 + this->buildings[buildingID].fireDuration;
                int base = 8;
                if ((int)this->buildings[buildingID].widthOrHeight > 6) {
                    base = 16;
                }
                interval = (base - this->buildings[buildingID].widthOrHeight) * 5;
            }
            if (tick % interval != 0) {
                return;
            }

            int microX = (SEC_RNG::instance.currentNumber2 % (int)this->buildings[buildingID].widthOrHeight
                             + (short)this->buildings[buildingID].x)
                * 8;
            int microY = ((SEC_RNG::instance.currentNumber2 >> 8) % (int)this->buildings[buildingID].widthOrHeight
                             + (short)this->buildings[buildingID].y)
                * 8;
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(5,
                playerID, 0, microX, microY,
                DAT_TileMapState::instance.HeightLayer[this->buildings[buildingID].currentTilePositionAdjusted], microX,
                microY, DAT_TileMapState::instance.HeightLayer[this->buildings[buildingID].currentTilePositionAdjusted],
                (EntityType)0x20, 0);
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
            if ((SEC_RNG::instance.currentNumber1 & 1) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    microX / 8, microY / 8, OpenSHC::DE::SHCDE::FX_FIRE_POP);
            }
        }

    }
}
}
