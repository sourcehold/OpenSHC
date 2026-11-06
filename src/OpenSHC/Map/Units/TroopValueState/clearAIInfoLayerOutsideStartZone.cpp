#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B680
        void TroopValueState::clearAIInfoLayerOutsideStartZone()
        {
            int const startArea = DAT_TroopValueState::instance.attackInfo.startCon;
            for (int tile = 0; tile < OpenSHC::Map::MC_MAP_TILES_COUNT; ++tile) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] != 0
                    && (short)DAT_TileMapState::instance.PathConnectionLayer[tile] != startArea) {
                    DAT_TileMapState::instance.AIInfoLayer[tile] = 0;
                }
            }
        }

    }
}
}
