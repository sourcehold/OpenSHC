#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005014F0
    void Version::UpgradeMapLogicToVersion_120()
    {
        for (int tile = 0; tile < OpenSHC::Map::MC_MAP_TILES_COUNT; ++tile) {
            byte height = DAT_TileMapState::instance.HeightLayer[tile];
            DAT_TileMapState::instance.DefaultHeightLayer[tile] = height;
            int logic = DAT_TileMapState::instance.LogicLayer[tile];
            if ((logic & 0x200) != 0) {
                DAT_TileMapState::instance.DefaultHeightLayer[tile] = height - 98;
            } else if ((logic & 0x800) != 0) {
                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int count = 0;
                int sum = 0;
                int i;
                for (i = 0; i < 8; ++i) {
                    int neighbour = ((int*)DAT_TileMapState::instance.directionTranslationMatrix)
                                        [DAT_UnitPropertiesDefinedData::instance.field84_0x11cb4[i] + y * 8]
                        + i;
                    int neighbourLogic = DAT_TileMapState::instance.LogicLayer[neighbour];
                    if ((neighbourLogic & 0x800) == 0) {
                        if ((neighbourLogic & 0x200) != 0) {
                            sum += DAT_TileMapState::instance.HeightLayer[neighbour] - 98;
                        } else if ((neighbourLogic & 0x100) != 0) {
                            sum += DAT_TileMapState::instance.HeightLayer[neighbour] - 90;
                        } else {
                            sum += DAT_TileMapState::instance.HeightLayer[neighbour];
                        }
                        count += 1;
                    }
                }
                // Faithful quirk: the result is stored at the loop index, not at the tile
                if (count == 0) {
                    DAT_TileMapState::instance.DefaultHeightLayer[i] = 8;
                } else {
                    DAT_TileMapState::instance.DefaultHeightLayer[i] = (byte)(sum / count);
                }
            } else if ((logic & 0x100) != 0) {
                DAT_TileMapState::instance.DefaultHeightLayer[tile] = height - 90;
            }
        }
    }

}
}
