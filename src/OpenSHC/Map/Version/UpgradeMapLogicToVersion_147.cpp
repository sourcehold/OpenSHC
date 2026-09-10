#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501730
    void Version::UpgradeMapLogicToVersion_147()
    {
        for (int _tile = 0; _tile < 80400; _tile++) {
            if (156 < DAT_TileMapState::instance.DefaultHeightLayer[_tile]) {
                DAT_TileMapState::instance.HeightLayer[_tile] = DAT_TileMapState::instance.HeightLayer[_tile]
                    + (156 - DAT_TileMapState::instance.DefaultHeightLayer[_tile]);
                DAT_TileMapState::instance.DefaultHeightLayer[_tile] = 156;
            }
        }
    }

}
}
