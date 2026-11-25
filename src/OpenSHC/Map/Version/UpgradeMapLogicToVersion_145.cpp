#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005016D0
    void Version::UpgradeMapLogicToVersion_145()
    {
        for (int tile = 0; tile < OpenSHC::Map::MC_MAP_TILES_COUNT; ++tile) {
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 1) != 0) {
                DAT_TileMapState::instance.HeightLayer[tile] = 0;
                DAT_TileMapState::instance.DefaultHeightLayer[tile] = 0;
            }
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x100000) == 0
                && (DAT_TileMapState::instance.Logic2Layer[tile] & 0x20) != 0) {
                DAT_TileMapState::instance.HeightLayer[tile] = 0;
                DAT_TileMapState::instance.DefaultHeightLayer[tile] = 0;
            }
            DAT_TileMapState::instance.LogicLayer[tile] &= ~0x4c;
        }
    }

}
}
