#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005011C0
    void Version::UpgradeMapLogicToVersion_125()
    {
        for (int i = 0; i < 80400; i++) {
            if (DAT_TileMapState::instance.HeightLayer[i] == 80) {
                DAT_TileMapState::instance.Logic2Layer[i] = 4;
            } else if (DAT_TileMapState::instance.HeightLayer[i] == 130) {
                DAT_TileMapState::instance.Logic2Layer[i] = 8;
            }
        }
    }

}
}
