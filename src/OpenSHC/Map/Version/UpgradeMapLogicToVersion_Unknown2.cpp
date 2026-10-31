#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501350
    void Version::UpgradeMapLogicToVersion_Unknown2()
    {
        for (int tile = 0; tile < OpenSHC::Map::MC_MAP_TILES_COUNT; ++tile) {
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x800) != 0
                && DAT_TileMapState::instance.HeightLayer[tile]
                    <= DAT_TileMapState::instance.DefaultHeightLayer[tile]) {
                DAT_TileMapState::instance.HeightLayer[tile] = DAT_TileMapState::instance.DefaultHeightLayer[tile];
                DAT_TileMapState::instance.LogicLayer[tile] &= ~0x100;
                DAT_TileMapState::instance.LogicLayer[tile] &= ~0x200;
                DAT_TileMapState::instance.LogicLayer[tile] &= ~0x800;
                DAT_TileMapState::instance.LogicLayer[tile] &= ~0x10000;
                DAT_TileMapState::instance.LogicLayer[tile] &= ~0x400000;
            }
        }
    }

}
}
