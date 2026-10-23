#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Entities::EntityType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC490
    void TileMapState::generateDustClouds()
    {
        short seed = SEC_RNG::instance.currentNumber2;
        int random = SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        this->SEC_Section1052 = this->SEC_Section1052 + 1;
        if (random % 500 == this->SEC_Section1052 % 500) {
            this->SEC_Section1053 = random % 0xb4;
        }
        if (random % 0x4b0 == this->SEC_Section1052 % 0x4b0) {
            this->SEC_Section1054 = random % 0xb4;
        }
        if (this->SEC_Section1053 != 0) {
            this->SEC_Section1053 = this->SEC_Section1053 - 1;
        }
        if (this->SEC_Section1054 != 0) {
            this->SEC_Section1054 = this->SEC_Section1054 - 1;
        }

        for (int i = 0; i < this->temporaryTerrainTypeIndex; i++) {
            int tile = this->temporaryTerrainTypeArray[i];
            /* one tile out of every 64 puffs, selected by the tile's own random value */
            if ((short)(this->RandomLayer[tile] ^ seed) % 64 != this->SEC_Section1052 % 64) {
                continue;
            }
            int stage = this->temporaryTerrainTypeBinaryArray[i];
            if (stage == 0) {
                if (this->SEC_Section1054 != 0) {
                    continue;
                }
            } else {
                if (this->SEC_Section1053 != 0) {
                    continue;
                }
                if (stage != 1) {
                    stage = 2;
                }
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, 0, 0,
                (tile - DAT_ViewportRenderState::instance.translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]].addXgetTile) * 8 + 4,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] * 8 + 4, this->HeightLayer[tile], 0, 0, 0,
                OpenSHC::Map::Entities::ET_DUST_CLOUD, stage);
        }
    }

}
}
