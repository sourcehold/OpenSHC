#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FAF70
    void TileMapState::clearStockpileFootprintTiles(int x, int y)
    {
        for (int i = 0; i < 9; ++i) {
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[y + DAT_TerrainDefinedData::instance.StockpilePathableOffsets[i].y]
                           .addXgetTile
                + x + DAT_TerrainDefinedData::instance.StockpilePathableOffsets[i].x;

            this->LogicLayer[tile] &= ~0x102;
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            if (DAT_BuildingsState::instance.buildings[this->AlphaGFXLayer[tile]].noRubble == 0) {
                this->BuildingWasLayer[tile] = 0;
            } else {
                this->MiscDisplayLayer[tile] |= 0x4000;
            }
            this->AlphaGFXLayer[tile] = 0;
        }
    }

}
}
