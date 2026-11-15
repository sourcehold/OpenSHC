#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Entities::EntityType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC490
    void TileMapState::generateDustClouds()
    {
        int const seed = SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        this->SEC_Section1052 += 1;
        if (seed % 500 == this->SEC_Section1052 % 500) {
            this->SEC_Section1053 = seed % 180;
        }
        if (seed % 1200 == this->SEC_Section1052 % 1200) {
            this->SEC_Section1054 = seed % 180;
        }
        if (this->SEC_Section1053 != 0) {
            this->SEC_Section1053 -= 1;
        }
        if (this->SEC_Section1054 != 0) {
            this->SEC_Section1054 -= 1;
        }

        for (int i = 0; i < this->temporaryTerrainTypeIndex; i++) {
            // one tile out of every 64 puffs, selected by the tile's own random value
            if ((this->RandomLayer[this->temporaryTerrainTypeArray[i]] ^ seed) % 64 != this->SEC_Section1052 % 64) {
                continue;
            }
            int const tileY = DAT_ViewportRenderState::instance
                                  .tileTranslationMatrix_YComponent[this->temporaryTerrainTypeArray[i]];
            int const tileX = this->temporaryTerrainTypeArray[i]
                - DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile;
            int const stage = this->temporaryTerrainTypeBinaryArray[i];
            if (stage == 0) {
                if (this->SEC_Section1054 == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, 0, 0,
                        tileX * 8 + 4, tileY * 8 + 4, this->HeightLayer[this->temporaryTerrainTypeArray[i]], 0, 0, 0,
                        OpenSHC::Map::Entities::ET_DUST_CLOUD, stage);
                }
            } else if (this->SEC_Section1053 == 0) {
                if (stage == 1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, 0, 0,
                        tileX * 8 + 4, tileY * 8 + 4, this->HeightLayer[this->temporaryTerrainTypeArray[i]], 0, 0, 0,
                        OpenSHC::Map::Entities::ET_DUST_CLOUD, stage);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, 0, 0,
                        tileX * 8 + 4, tileY * 8 + 4, this->HeightLayer[this->temporaryTerrainTypeArray[i]], 0, 0, 0,
                        OpenSHC::Map::Entities::ET_DUST_CLOUD, 2);
                }
            }
        }
    }

}
}
