#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501760
    void Version::UpgradeMapLogicToVersion_Unknown3()
    {
        for (int moatID = 0; moatID < 16000; ++moatID) {
            // The moat tile is read as a full dword
            if (DAT_TileMapState::instance.moats[moatID].owner != 0
                && DAT_TileMapState::instance.moats[moatID].stage == 1
                && (DAT_TileMapState::instance.LogicLayer[*(uint*)&DAT_TileMapState::instance.moats[moatID].tile]
                       & 0x40000000)
                    != 0) {
                DAT_TileMapState::instance.moats[moatID].stage = 2;
                DAT_TileMapState::instance.moats[moatID].fillProgress = 4;
            }
        }
    }

}
}
