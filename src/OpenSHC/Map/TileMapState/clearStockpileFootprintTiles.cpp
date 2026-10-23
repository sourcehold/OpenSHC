#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FAF70
    void TileMapState::clearStockpileFootprintTiles(int x, int y)
    {
        int tile;
        for (int offset = 0; offset < 9; offset += 3) {
            tile = DAT_ViewportRenderState::instance
                       .translationMatrix[DAT_TerrainDefinedData::instance.StockpilePathableOffsets[offset + 0].y + y]
                       .addXgetTile
                + x + DAT_TerrainDefinedData::instance.StockpilePathableOffsets[offset + 0].x;
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_STOCKPILEUnk | L_WALL_OR_GATEHOUSE);
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            if (DAT_BuildingsState::instance.buildings[this->AlphaGFXLayer[tile]].noRubble == 0) {
                this->BuildingWasLayer[tile] = 0;
            } else {
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 0x4000;
            }
            this->AlphaGFXLayer[tile] = 0;
            tile = DAT_ViewportRenderState::instance
                       .translationMatrix[DAT_TerrainDefinedData::instance.StockpilePathableOffsets[offset + 1].y + y]
                       .addXgetTile
                + x + DAT_TerrainDefinedData::instance.StockpilePathableOffsets[offset + 1].x;
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_STOCKPILEUnk | L_WALL_OR_GATEHOUSE);
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            if (DAT_BuildingsState::instance.buildings[this->AlphaGFXLayer[tile]].noRubble == 0) {
                this->BuildingWasLayer[tile] = 0;
            } else {
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 0x4000;
            }
            this->AlphaGFXLayer[tile] = 0;
            tile = DAT_ViewportRenderState::instance
                       .translationMatrix[DAT_TerrainDefinedData::instance.StockpilePathableOffsets[offset + 2].y + y]
                       .addXgetTile
                + x + DAT_TerrainDefinedData::instance.StockpilePathableOffsets[offset + 2].x;
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_STOCKPILEUnk | L_WALL_OR_GATEHOUSE);
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            if (DAT_BuildingsState::instance.buildings[this->AlphaGFXLayer[tile]].noRubble == 0) {
                this->BuildingWasLayer[tile] = 0;
            } else {
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 0x4000;
            }
            this->AlphaGFXLayer[tile] = 0;
        }
    }

}
}
