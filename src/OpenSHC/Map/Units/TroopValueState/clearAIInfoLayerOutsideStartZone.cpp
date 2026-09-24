#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B680
        void TroopValueState::clearAIInfoLayerOutsideStartZone()
        {
            int const startArea = DAT_TroopValueState::instance.attackInfo.startCon;
            for (int tile = 0; tile < 80400; ++tile) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] != 0
                    && (short)DAT_TileMapState::instance.PathConnectionLayer[tile] != startArea) {
                    DAT_TileMapState::instance.AIInfoLayer[tile] = 0;
                }
            }
        }

    }
}
}
