#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005011C0
    void Version::UpgradeMapLogicToVersion_125()
    {
        for (int tile = 0; tile < 80400; ++tile) {
            if (DAT_TileMapState::instance.HeightLayer[tile] == 80) {
                DAT_TileMapState::instance.Logic2Layer[tile] = 4;
            } else if (DAT_TileMapState::instance.HeightLayer[tile] == 130) {
                DAT_TileMapState::instance.Logic2Layer[tile] = 8;
            }
        }
    }

}
}
