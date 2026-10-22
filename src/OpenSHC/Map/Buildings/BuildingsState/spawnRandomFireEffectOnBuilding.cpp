#include "../BuildingsState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x00410800
        void BuildingsState::spawnRandomFireEffectOnBuilding(int buildingID, undefined4 playerID)
        {
            if (this->buildings[buildingID].fireDuration < 400) {
                return;
            }
            int const size = this->buildings[buildingID].widthOrHeight;
            int interval;
            if (size <= 3) {
                interval = 24 - size * 5;
            } else if (size <= 6) {
                interval = (8 - size) * 5;
            } else {
                interval = (16 - size) * 5;
            }
            if ((this->buildings[buildingID].fireRelatedRNG1 + this->buildings[buildingID].fireDuration) % interval
                != 0) {
                return;
            }
            int const height
                = DAT_TileMapState::instance.HeightLayer[this->buildings[buildingID].currentTilePositionAdjusted];
            int const x = (SEC_RNG::instance.currentNumber2 % (int)this->buildings[buildingID].widthOrHeight
                              + this->buildings[buildingID].x)
                * 8;
            int const y = ((SEC_RNG::instance.currentNumber2 >> 8) % (int)this->buildings[buildingID].widthOrHeight
                              + this->buildings[buildingID].y)
                * 8;
            // EntityType has no constant for 32.
            MACRO_CALL_MEMBER(Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(
                5, playerID, 0, x, y, height, x, y, height, (Entities::EntityType)32, 0);
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
            if ((SEC_RNG::instance.currentNumber1 & 1) != 0) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    x / 8, y / 8, DE::SHCDE::FX_FIRE_POP);
            }
        }

    }
}
}
