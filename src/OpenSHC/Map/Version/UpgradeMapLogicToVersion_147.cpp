#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501730
    void Version::UpgradeMapLogicToVersion_147()
    {
        for (int tile = 0; tile < 80400; ++tile) {
            if (DAT_TileMapState::instance.DefaultHeightLayer[tile] > 156) {
                DAT_TileMapState::instance.HeightLayer[tile]
                    += 156 - DAT_TileMapState::instance.DefaultHeightLayer[tile];
                DAT_TileMapState::instance.DefaultHeightLayer[tile] = 156;
            }
        }
    }

}
}
