#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_SEA;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FC340
    void TileMapState::collectCliffEdgeTilesForClimbData()
    {
        this->temporaryTerrainTypeIndex = 0;
        for (int tile = 0; tile < MC_MAP_TILES_COUNT; tile++) {
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                continue;
            }

            if ((this->LogicLayer[tile] & L_RIVER) != 0
                && (this->Logic2Layer[tile] & L2_STONES_OR_DRIVEN_SANDUnk) != 0) {
                this->temporaryTerrainTypeBinaryArray[this->temporaryTerrainTypeIndex] = 1;
                this->temporaryTerrainTypeArray[this->temporaryTerrainTypeIndex] = tile;
                int const row = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int const height = this->HeightLayer[tile];
                for (int index = 0; index < 8; index++) {
                    int neighbour
                        = this->directionTranslationMatrix[row][DAT_ClimbLogicDefinedData::instance.field_0x2c[index]]
                        + tile;
                    if ((this->LogicLayer[neighbour] & L_RIVER) != 0 && this->HeightLayer[neighbour] > height + 80) {
                        this->temporaryTerrainTypeBinaryArray[this->temporaryTerrainTypeIndex] = 0;
                        break;
                    }
                }
                this->temporaryTerrainTypeIndex += 1;
                if ((int)this->temporaryTerrainTypeIndex >= 1000) {
                    return;
                }
            }

            if (((this->LogicLayer[tile] & L_RIVER) != 0 && (this->Logic2Layer[tile] & L2_OASIS_GRASS) != 0)
                || ((this->LogicLayer[tile] & L_SEA) != 0 && (this->Logic2Layer[tile] & L2_PLATEAU_HIGH) != 0)) {
                this->temporaryTerrainTypeBinaryArray[this->temporaryTerrainTypeIndex] = 1;
                this->temporaryTerrainTypeArray[this->temporaryTerrainTypeIndex] = tile;
                this->temporaryTerrainTypeIndex += 1;
                if ((int)this->temporaryTerrainTypeIndex >= 1000) {
                    return;
                }
            }
        }
    }

}
}
