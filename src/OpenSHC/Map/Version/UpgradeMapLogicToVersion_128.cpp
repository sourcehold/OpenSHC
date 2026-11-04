#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501440
    void Version::UpgradeMapLogicToVersion_128()
    {
        for (int tile = 0; tile < OpenSHC::Map::MC_MAP_TILES_COUNT; ++tile) {
            if ((DAT_TileMapState::instance.LogicLayer[tile] & 0x40000000) != 0) {
                int moatID = MACRO_CALL_MEMBER(TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(tile);
                if (moatID != 0 && DAT_TileMapState::instance.moats[moatID].stage == 2
                    && DAT_TileMapState::instance.moats[moatID].fillProgress == 4) {
                    DAT_TileMapState::instance.HeightLayer[tile] = 0;
                }
            }
        }
    }

}
}
